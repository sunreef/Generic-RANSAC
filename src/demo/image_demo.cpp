//
// Created by victor on 14/12/15.
//


#include "demo/image_demo.h"


void ImageDemo::demo() {
    Mat I1 = imread("../img/image0006.jpg");
    Mat I2 = imread("../img/image0007.jpg");

    Mat I2temp(I2.rows, I1.cols + I2.cols, CV_8UC3);

    for (int i = 0; i < I2.rows; i++) {
        for (int j = 0; j < I2.cols; j++) {
            I2temp.at<Vec3b>(i, j + I1.cols) = I2.at<Vec3b>(i, j);
        }
    }

    I2 = I2temp;

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

//        if (dist1 < 0.5 * dist2) {
            KeyPoint k1 = kpts1[v[0].queryIdx];
            KeyPoint k2 = kpts2[v[0].trainIdx];
            pts1.push_back(k1);
            pts2.push_back(k2);
            p.push_back(Homography::Pair(k2.pt, k1.pt));
//            trueMatches.push_back(DMatch(pts1.size() - 1, pts2.size() - 1, dist1));
//        }
    }

    std::cout << p.size() << std::endl;

    RANSAC<Homography, Homography::Pair, HomographyFromPoints, DistancePointFromHomography, HomographyError> r(5, p,
                                                                                                               1000, 20,
                                                                                                               270,
                                                                                                               HomographyFromPoints(),
                                                                                                               DistancePointFromHomography(),
                                                                                                               HomographyError());
    Mat result;
    Homography homo = r.findBestFit();



    warpPerspective(I2, result, homo.H, Size( I2.cols, I1.rows));
    for (int i = 0; i < I1.rows; i++) {
        for (int j = 0; j < I1.cols; j++) {
            result.at<Vec3b>(i, j) = I1.at<Vec3b>(i, j);
        }
    }


//    vector<KeyPoint> ptFinal1, ptFinal2;
//
//    for(Homography::Pair pair : r.inliers) {
//        ptFinal1.push_back(KeyPoint(pair.first));
//        ptFinal2.push_back(pair.second);
//        trueMatches.push_back(DMatch(ptFinal1.size()-1, ptFinal2.size() - 1, 0.0));
//    }


//    Mat match;
//    drawMatches(I1, pts1, I2, pts2, trueMatches, match);

//    imshow("Matches", match);
    imshow("result", result);
    waitKey();

}