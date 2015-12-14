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

template<class Point, class Model, int N>
class RANSAC {

public:
    RANSAC(Model m, vector<Point> points, int iterations, double error, int minimum) :
            model(m), data(points), k(iterations), t(error), d(minimum) {
    }

    Model model;
    vector<Point> data;
    int k;
    double t;
    int d;

    Model findBestFit() {

        if (N > data.size()) {
            std::cout << "Not enough points given." << std::endl;
        }

        int i = 0;
        Model bestFit = model;
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
            Model M(maybeInliers.begin(), maybeInliers.end(), exists);

            if(!exists) {
                std::cout << "Not enough points to fit the model";
                return model;
            }

            std::vector<Point> alsoInliers;
            for (int index = 0; index < data.size(); index++) {
                if (indices.find(index) == indices.end()) {
                    if (M.distance(data[index]) < t) {
                        alsoInliers.push_back(data[index]);
                    }
                }
            }

            if (alsoInliers.size() > d) {
                for (Point p : alsoInliers) {
                    maybeInliers.push_back(p);
                }

                Model betterModel(maybeInliers.begin(), maybeInliers.end(), exists);
                if(!exists) {
                    std::cout << "Not enough points to fit the model";
                    return model;
                }

                double error = M.error(maybeInliers.begin(), maybeInliers.end());

                if (error < bestError) {
                    bestFit = betterModel;
                    bestError = error;
                }
            }

            i++;
        }

        return bestFit;

    }

    double modelError(Model m, std::vector<Point> points) {
        double error = 0;

        for (Point p: points) {
            error += m.distance(p);
        }
        return error;
    }
};


#endif //OPENCV_BASE_RANSAC_H
