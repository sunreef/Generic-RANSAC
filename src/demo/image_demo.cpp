
#include "demo/image_demo.h"


Mat ImageDemo::findHomography(Mat I1, Mat I2) {
    vector<KeyPoint> kpts1, kpts2;
    Mat desc1, desc2;

    Ptr<AKAZE> akaze = AKAZE::create();
    akaze->detectAndCompute(I1, noArray(), kpts1, desc1);
    akaze->detectAndCompute(I2, noArray(), kpts2, desc2);

    BFMatcher bfm(NORM_L2);
    vector<vector<DMatch>> matches;
    bfm.knnMatch(desc1, desc2, matches, 2);

    vector<DMatch> trueMatches;
    vector<KeyPoint> pts1, pts2;
    vector<Homography::Pair> p;

    for (vector<DMatch> v: matches) {
        float dist1 = v[0].distance;
        float dist2 = v[1].distance;

        if (dist1 < 0.7 * dist2) {
            KeyPoint k1 = kpts1[v[0].queryIdx];
            KeyPoint k2 = kpts2[v[0].trainIdx];
            pts1.push_back(k1);
            pts2.push_back(k2);
            p.push_back(Homography::Pair(k2.pt, k1.pt));
            trueMatches.push_back(DMatch(pts1.size() - 1, pts2.size() - 1, dist1));
        }
    }

    std::cout << p.size() << std::endl;

    RANSAC<Homography, Homography::Pair, HomographyFromPoints, DistancePointFromHomography, HomographyError> r(4,
                                                                                                               p,
                                                                                                               1000,
                                                                                                               3,
                                                                                                               80,
                                                                                                               HomographyFromPoints(),
                                                                                                               DistancePointFromHomography(),
                                                                                                               HomographyError());
    Homography homo = r.findBestFit();

    return homo.H;
}


vector<Mat> ImageDemo::findHomographies(vector<string> filenames) {

    Mat I1 = imread(filenames[0]), I2;
    vector<Mat> homographies;
    for (int i = 1; i < filenames.size(); i++) {
        I2 = imread(filenames[i]);
        homographies.push_back(findHomography(I1, I2));
        I1 = I2;
    }
    return homographies;
}

void ImageDemo::demo() {

    vector<string> filenames;

    /*
     * On récupère les chemins des fichiers d'images.
     */

    for (int img = 26; img <= 35; img++) {
        filenames.push_back("../img/pano1/IMG_00" + std::to_string(img) + ".JPG");
    }

    /*
     * On calcule les homographies entre chaque paire d'images consécutives.
     */
    vector<Mat> homographies = findHomographies(filenames);


    /*
     * On recompose l'image finale en ajoutant les photos déformées une par une.
     */
    Mat result;
    Mat I2 = imread(filenames[filenames.size() - 1]);

    for (int i = filenames.size() - 2; i >= 0; i--) {
        Mat I1 = imread(filenames[i]);
        warpPerspective(I2, result, homographies[i], Size(I2.cols + I1.cols, I1.rows));
        for (int k = 0; k < I1.rows; k++) {
            for (int j = 0; j < I1.cols - 5; j++) {
                Vec3b temp = I1.at<Vec3b>(k, j);
                int sum = int(temp[0]) + temp[1] + temp[2];
                if (sum > 20) {
                    result.at<Vec3b>(k, j) = I1.at<Vec3b>(k, j);
                }
            }
        }
        I2 = result;
        imshow("Result", I2);
        waitKey();
    }

    imwrite("result.jpg", I2);

    waitKey();

}