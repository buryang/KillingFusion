//
// Created by Saurabh Khanduja on 18.10.18.
//

#ifndef INC_3DSCANNINGANDMOTIONCAPTURE_DATASETREADER_H
#define INC_3DSCANNINGANDMOTIONCAPTURE_DATASETREADER_H

#include <string>
#include <vector>
#include <config.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

class DatasetReader
{
private:
  std::string m_imageDir;
  Eigen::Matrix3f m_depthIntrinsicMatrix;
  int m_numImageFiles;
  int m_depthHeight, m_depthWidth;
  std::pair<float, float> m_minMaxDepth;

  std::vector<float> LoadMatrixFromFile(std::string filename, int M);
  cv::Mat readDepthImage(std::string depthFilename);
  void analyzeMinMaxDepthValues();

public:
  DatasetReader() = delete;

  DatasetReader(std::string DatasetRootDir, DEFORMABLE_DATASET dataset);

  std::vector<cv::Mat> getImages(int frameIndex);

  int getNumImageFiles() const;
  int getDepthHeight();
  int getDepthWidth();
  Eigen::Matrix3f getDepthIntrinsicMatrix();

  float getMinimumDepthThreshold() { return m_minMaxDepth.first; }
  float getMaximumDepthThreshold() { return m_minMaxDepth.second; }
  
  // Hard Coded values
  static float getVoxelSize() { return 0.01; }
  static float getTruncationDistanceInVoxelSize() { return 3.0; }
};

#endif //INC_3DSCANNINGANDMOTIONCAPTURE_DATASETREADER_H