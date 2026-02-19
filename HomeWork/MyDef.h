#pragma once

#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include<algorithm>

#include <vtk-8.2/vtkActor.h>
#include <vtk-8.2/vtkContourFilter.h>
#include <vtk-8.2/vtkMath.h>
#include <vtk-8.2/vtkNamedColors.h>
#include <vtk-8.2/vtkPointData.h>
#include <vtk-8.2/vtkPolyDataMapper.h>
#include <vtk-8.2/vtkProperty.h>
#include <vtk-8.2/vtkRenderWindow.h>
#include <vtk-8.2/vtkRenderWindowInteractor.h>
#include <vtk-8.2/vtkRenderer.h>
#include <vtk-8.2/vtkShortArray.h>
#include <vtk-8.2/vtkStructuredPoints.h>
#include <vtk-8.2/vtkCardinalSpline.h>
#include <vtk-8.2/vtkSphereSource.h>
#include <vtk-8.2/vtkGlyph3D.h>
#include <vtk-8.2/vtkTubeFilter.h>
#include <vtk-8.2/vtkContextView.h>
#include <vtk-8.2/vtkChartXY.h>
#include <vtk-8.2/vtkTable.h>
#include <vtk-8.2/vtkFloatArray.h>
#include <vtk-8.2/vtkDoubleArray.h>
#include <vtk-8.2/vtkContextScene.h>
#include <vtk-8.2/vtkPlot.h>

class CExSplitterWnd;
class CHomeWork1App;
class CHomeWork1Doc;
class CHomeWork1View;
class CMainFrame;
class CParamsView;
class CHWStatView;
class CHWAnaView;
#include "ParamsView.h"
#include "ExSplitterWnd.h"
#include "HomeWork1.h"
#include "HomeWork1Doc.h"
#include "HomeWork1View.h"
#include "MainFrm.h"
#include "HWStatView.h"
#include "HWAnaView.h"

extern std::vector<double> data1;
extern std::vector<double> data2;
extern std::vector<double> sortdata;
extern std::vector<double> gdata;
extern std::vector<double> acdata;
using namespace std;


void GenData(vector<double>& data,int len,const double mean, const double stddev);
void SortData(vector<double>& data, vector<double>& out);
void ACData(vector<double>& data, vector<double>& out);

