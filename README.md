````markdown
# Object-Oriented Programming Technology Program Design Report  
## Title: Gaussian Sequence Generation

**Name:** Muhammad Altaf 
**Department:** Information and Communication Engineering 
**Student ID:** 12009030  

### 1. Problem Analysis  
In scientific research, we often encounter issues related to data processing. The topic chosen for this assignment is Gaussian random distribution sequences and their statistical properties. Gaussian noise is a very common type of noise used in algorithm design and simulation processes to simulate environmental or process noise. Noise refers to voltage or current in circuits or systems that does not carry any useful information. In industry and nature, there are various sources of interference (noise sources), such as the connection of high-power electronic devices, the switching on and off of large power-consuming equipment, and lightning strikes. These sources cause orderly or disorderly changes in the electric and magnetic fields in space, and all these are interference sources (or noise sources). Gaussian noise refers to a type of noise whose probability density function follows a Gaussian (normal) distribution. If a noise’s amplitude distribution follows a Gaussian distribution and its power spectral density is uniformly distributed, it is called Gaussian white noise. Gaussian white noise has an uncorrelated second moment and a constant first moment, referring to the time correlation of the signal. This assignment aims to implement the generation and visualization of Gaussian sequences, primarily including the generation of probability density functions and autocorrelation functions.

### 2. Algorithm Selection  
A Gaussian process is a type of random process in probability theory and mathematical statistics, formed by a series of random variables that follow a normal distribution over an index set. If a random variable \(X\) follows a normal distribution with mean \(\mu\) and variance \(\sigma^2\), it is denoted as \(N(\mu, \sigma^2)\), and its probability density function is determined by the mean \(\mu\) and standard deviation \(\sigma\). When \(\mu = 0, \sigma = 1\), it represents the standard normal distribution.  
If a random variable follows a probability distribution with a location parameter \(\mu\) and a scale parameter \(\sigma\), and its probability density function is:

\[
f(x) = \frac{1}{\sqrt{2\pi\sigma^2}} \exp\left(-\frac{(x - \mu)^2}{2\sigma^2}\right)
\]

then this random variable is called a normal random variable. The distribution that this random variable follows is called the normal distribution, denoted as \(X \sim N(\mu, \sigma^2)\).  

The mean and variance of a Gaussian sequence are defined as:

\[
\text{Mean of Gaussian Sequence} = \mu
\]
\[
\text{Variance of Gaussian Sequence} = \sigma^2
\]

Where \(n\) represents the number of points in the Gaussian sequence.

### 3. Solution Design  
#### 1. Program Flow  
(Insert flowchart here)

#### 2. Specific Implementation  
The experiment uses multithreading to implement the Gaussian sequence generation. The program reads user input data (or uses default values if no input is provided), generates a Gaussian random distribution sequence based on the input data, and plots the autocorrelation function and probability density function based on the generated sample points. The user can set the refresh rate per second to control the frequency of the image refresh display. During program execution, the user can pause the program using the "Pause" button or stop it using the "Stop" button.

### 4. Programming Implementation  
#### 1. Programming Environment  
The software environment used for this experiment is Visual Studio 2019 Community on Windows 10, and the third-party library used is the compiled VTK library.

#### 2. Code Implementation  
1) **Generate Sample Points:**

```cpp
void GenData(vector<double>& data, int len, const double mean, const double stddev) {
    std::default_random_engine generator;
    std::normal_distribution<double> dist(mean, stddev);

    data.clear();
    for (int i = 0; i < len; i++) {
        double d = dist(generator);
        data.push_back(d);
    }
}
````

2. **Draw Scatter Plot:**

```cpp
int CHWAnaView::DrawSine(std::vector<double>& data) {
    int status = EXIT_SUCCESS;
    view = vtkSmartPointer<vtkContextView>::New();
    chart = vtkSmartPointer<vtkChartXY>::New();
    table = vtkSmartPointer<vtkTable>::New();
    
    arrI = vtkSmartPointer<vtkDoubleArray>::New();
    arrX = vtkSmartPointer<vtkDoubleArray>::New();
    arrY = vtkSmartPointer<vtkDoubleArray>::New();

    CRect rect;
    GetClientRect(rect);
    view->GetRenderWindow()->SetSize(rect.Width(), rect.Height());
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetMultiSamples(0);

    view->GetScene()->AddItem(chart.GetPointer());

    arrI->SetName("Gauss Normal Random I");
    table->AddColumn(arrI.GetPointer());

    arrX->SetName("Gauss Normal Random X");
    table->AddColumn(arrX.GetPointer());
    
    arrY->SetName("Gauss Normal Random Y");
    table->AddColumn(arrY.GetPointer());

    int length = data.size();
    table->SetNumberOfRows(length);
    for (int i = 0; i < length; ++i) {
        double x = data1[i];
        table->SetValue(i, 0, double(i));
        table->SetValue(i, 1, x);
    }

    vtkPlot* line = chart->AddPlot(vtkChart::POINTS);
    line->SetInputData(table.GetPointer(), 0, 1);
    line->SetColor(0, 255, 0, 255);
    line->SetWidth(2.0);

    chart->SetShowLegend(true);
    view->GetRenderWindow()->SetParentId(m_hWnd);
    view->GetRenderWindow()->GetInteractor()->Initialize();
    view->GetRenderWindow()->Render();

    return 0;
}
```

3. **Calculate Probability Density Function:**

```cpp
void SortData(vector<double>& data, vector<double>& out) {
    out.clear();
    std::sort(out.begin(), out.end());
    for (int i = 0; i < out.size(); i++) {
        double j = 1 / exp((out[i] - m_mean) * (out[i] - m_mean) / (2 * m_cov * m_cov));
        gdata.push_back(j);
    }
}
```

4. **Draw Gaussian Distribution Probability Density Function:**

```cpp
void CHWStatView::DrawGussian(std::vector<double>& data) {
    int status = EXIT_SUCCESS;
    view = vtkSmartPointer<vtkContextView>::New();
    chart = vtkSmartPointer<vtkChartXY>::New();
    table = vtkSmartPointer<vtkTable>::New();
    arrC = vtkSmartPointer<vtkFloatArray>::New();
    arrS = vtkSmartPointer<vtkFloatArray>::New();
    arrS2 = vtkSmartPointer<vtkFloatArray>::New();
    arr1 = vtkSmartPointer<vtkFloatArray>::New();

    CRect rect;
    GetClientRect(rect);
    view->GetRenderWindow()->SetSize(rect.Width(), rect.Height());
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetMultiSamples(0);

    view->GetScene()->AddItem(chart.GetPointer());

    arrC->SetName("Cosine");
    table->AddColumn(arrC.GetPointer());

    arrS->SetName("Sine");
    table->AddColumn(arrS.GetPointer());

    arrS2->SetName("Gaussian");
    table->AddColumn(arrS2.GetPointer());

    arr1->SetName("One");
    table->AddColumn(arr1.GetPointer());
    
    int length = data.size();
    table->SetNumberOfRows(length);
    for (int i = 0; i < length; ++i) {
        double x = data[i];
        double y = gdata[i];
        table->SetValue(i, 0, x);
        table->SetValue(i, 2, y);
    }

    vtkPlot* line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table.GetPointer(), 0, 2);
    line->SetColor(0, 0, 255, 255);
    line->SetWidth(2.0);

    chart->SetShowLegend(true);
    view->GetRenderWindow()->SetParentId(m_hWnd);
    view->GetRenderWindow()->GetInteractor()->Initialize();
    view->GetRenderWindow()->Render();
}
```

5. **Calculate Autocorrelation Function:**

```cpp
void ACData(vector<double>& data, vector<double>& out) {
    for (int i = 0; i < data.size(); i++) {
        out.push_back(AutoCorrelation(data, i));
    }
}

double AutoCorrelation(std::vector<double>& data, int m) {
    double r = 0.0;
    for (int i = m; i < data.size(); i++) {
        r += data[i] * data[i - m];
    }
    r = r / (data.size() - m);
    return r;
}
```

6. **Draw Autocorrelation Function:**

```cpp
int CHomeWork1View::DrawAC(std::vector<double>& data) {
    int status = EXIT_SUCCESS;
    view = vtkSmartPointer<vtkContextView>::New();
    chart = vtkSmartPointer<vtkChartXY>::New();
    table = vtkSmartPointer<vtkTable>::New();

    arrI = vtkSmartPointer<vtkDoubleArray>::New();
    arrX = vtkSmartPointer<vtkDoubleArray>::New();
    arrY = vtkSmartPointer<vtkDoubleArray>::New();

    CRect rect;
    GetClientRect(rect);
    view->GetRenderWindow()->SetSize(rect.Width(), rect.Height());
    view->GetRenderer()->SetBackground(1.0, 1.0, 1.0);
    view->GetRenderWindow()->SetMultiSamples(0);

    view->GetScene()->AddItem(chart.GetPointer());

    arrI->SetName("Gauss Normal Random I");
    table->AddColumn(arrI.GetPointer());

    arrX->SetName("Autocorrelation Function");
    table->AddColumn(arrX.GetPointer());

    arrY->SetName("Gauss Normal Random Y");
    table->AddColumn(arrY.GetPointer());

    int length = data.size();
    table->SetNumberOfRows(2 * static_cast<vtkIdType>(length) - 1);

    for (int i = 1; i < length; ++i) {
        table->SetValue(static_cast<vtkIdType>(i)-1, 0, double(i-length));
        table->SetValue(static_cast<vtkIdType>(i)-1, 1, data[length-i]);
    }
    for (int i = 0; i < length; ++i) {
        table->SetValue(static_cast<vtkIdType>(i)+length-1, 0, double(i));
        table->SetValue(static_cast<vtkIdType>(i)+length-1, 1, data[i]);
    }
    vtkPlot* line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table.GetPointer(), 0, 1);
    line->SetColor(255, 0, 0, 255);
    line->SetWidth(2.0);

    chart->SetShowLegend(true);
    view->GetRenderWindow()->SetParentId(m_hWnd);
    view->GetRenderWindow()->GetInteractor()->Initialize();
    view->GetRenderWindow()->Render();
    return 0;
}
```

### 5. Operational Flow

1. **Set Parameters:** Set sequence mean, variance, sample size, and display refresh rate (default values are used if not specified).
2. **Start:** Click the Start button to begin generating and plotting.
3. **Pause:** Click the Pause button to pause generation.
4. **Stop:** Click the Stop button to stop generation and keep the current state.

```
```
