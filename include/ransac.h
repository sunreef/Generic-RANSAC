//
// Created by victor on 11/11/15.
//

#ifndef OPENCV_BASE_RANSAC_H
#define OPENCV_BASE_RANSAC_H

#include <vector>
#include <limits>
#include <random>
#include <set>
#include <array>
#include <iostream>

using std::vector;


template<class Model,class Point,  class ModelFromPoints, class DistancePointFromModel, class ModelError>
class RANSAC {

public:
    RANSAC(int n, vector<Point> points, int iterations, double error, int minimum, ModelFromPoints mfp,
           DistancePointFromModel dpm, ModelError me) :
            N(n), data(points), k(iterations), t(error), d(minimum), modelFromPoints(mfp),
            distancePointModel(dpm), modelError(me) {
    }

    Model model;
    vector<Point> data;
    int k;
    double t;
    int d;
    int N;
    ModelFromPoints modelFromPoints;
    DistancePointFromModel distancePointModel;
    ModelError modelError;

    vector<Point> inliers;

    Model findBestFit() {

        if (N > data.size()) {
            std::cout << "Not enough points given." << std::endl;
        }

        int i = 0;
        Model bestFit;
        double bestError = std::numeric_limits<double>::max();

        while (i < k) {
            std::set<int> indices;
            while (indices.size() < N) {
                int index = std::rand() % data.size();
                indices.insert(index);
            }
            std::vector<Point> maybeInliers;
            for (int u : indices) {
                maybeInliers.push_back(data[u]);
            }
            bool exists = true;
            Model M = modelFromPoints(maybeInliers.begin(), maybeInliers.end(), exists);

            if (!exists) {
                std::cout << "Not enough points to fit the model";
                return model;
            }

            std::vector<Point> alsoInliers;
            for (int index = 0; index < data.size(); index++) {
                if (indices.find(index) == indices.end()) {
                    if (distancePointModel(M, data[index]) < t) {
                        alsoInliers.push_back(data[index]);
                    }
                }
            }

            if (alsoInliers.size() > d) {
                for (Point p : alsoInliers) {
                    maybeInliers.push_back(p);
                }

                Model betterModel = modelFromPoints(maybeInliers.begin(), maybeInliers.end(), exists);
                if (!exists) {
                    std::cout << "Not enough points to fit the model";
                    return model;
                }

                double error = modelError(M, maybeInliers.begin(), maybeInliers.end());

                if (error < bestError) {
                    bestFit = betterModel;
                    bestError = error;
                    inliers = maybeInliers;
                }
            }

            i++;
        }

        return bestFit;

    }

    const vector<Point> &getInliers() {
        return inliers;
    }
};


#endif //OPENCV_BASE_RANSAC_H
