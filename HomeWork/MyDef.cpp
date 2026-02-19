#include "pch.h"
#include "MyDef.h"
#include"data.h"
// Example data

std::vector<double> data1;
std::vector<double> data2;
std::vector<double> sortdata;
std::vector<double> gdata;
std::vector<double> acdata;


double AutoCorrelation(std::vector<double>& data, int m);

void GenData(vector<double>& data,int len,const double mean,const double stddev)
{
    // Define random generator with Gaussian distribution
    std::default_random_engine generator;
    std::normal_distribution<double> dist(mean, stddev);

    // Add Gaussian noise
    data.clear();
    for (int i = 0; i < len;i++) {
        double d= dist(generator);
        data.push_back(d);
    }

}

void SortData(vector<double>& data, vector<double>& out)
{
    out.clear();
    gdata.clear();
    data2.clear();
    acdata.clear();
    out = data;
    data2 = data;
    std::sort(out.begin(), out.end());
    for (int i = 0; i < out.size(); i++) {
        double j = 1/exp((out[i] - m_mean) * (out[i] - m_mean) / (2 * m_cov * m_cov));
        gdata.push_back(j);
    }
}

void ACData(vector<double>& data, vector<double>& out)
{
    for (int i = 0; i < data.size(); i++) {
        out.push_back(AutoCorrelation(data, i));
    }
}

double AutoCorrelation(std::vector<double>&data, int m)
{
    double r = 0.0;
    for (int i = m; i < data.size(); i++)
    {
        r += data[i] * data[i - m];
    }
    r = r / (data.size() - m);
    return  r;
}