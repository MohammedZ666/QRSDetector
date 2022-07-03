#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include </home/abuobaidazishan/DevProjects/qrs_detector/utils.h>
#include<bits/stdc++.h>

using namespace std;

// QRSDetectorOffline class initialisation method.
// :param string ecg_data_path: path to the ECG dataset
// :param bool verbose: flag for printing the results
// :param bool log_data: flag for logging the results
// :param bool plot_data: flag for plotting the results to a file
// :param bool show_plot: flag for showing generated results plot - will not show anything if plot is not generated

// Configuration parameters.


vector<int> get_qrs_indices(vector<double> ecg_raw_data){

    int signal_frequency = 250;  // Set ECG device frequency in samples per second here.
    double filter_lowcut {0.0f};
    double filter_highcut {15.0f};
    double filter_order {1};

    int integration_window {15};  // Change proportionally when adjusting frequency (in samples).

    double findpeaks_limit {0.35};
    double findpeaks_spacing {50};  // Change proportionally when adjusting frequency (in samples).

    int refractory_period{120};  // Change proportionally when adjusting frequency (in samples).
    double qrs_peak_filtering_factor {0.125f};
    double noise_peak_filtering_factor {0.125f};
    double qrs_noise_diff_weight  {0.25};

    // Loaded ECG data.
    //double ecg_data_raw []{};

    // Measured and calculated values.
    vector <double> filtered_ecg_measurements;
    vector <double> differentiated_ecg_measurements;
    vector <double> squared_ecg_measurements;
    vector <double> integrated_ecg_measurements;
    vector <int> detected_peaks_indices;
    vector <double> detected_peaks_values;

    double qrs_peak_value {0.0f};
    double noise_peak_value {0.0f};
    double threshold_value = {0.0f};

    // Detection results.
    // qrs_peaks_indices = np.array([], dtype=int)
    // noise_peaks_indices = np.array([], dtype=int)

    // Final ECG data and QRS detection results array - samples with detected QRS are marked with 1 value.
    //ecg_data_detected = None

    return detected_peaks_indices;
}

vector<double> load_data_from_file(const char* path){
    std::ifstream file(path);
    vector<double> ecg_data;
    if (file.is_open()) {
        string line;
        bool is_first_line = true;
        while (std::getline(file, line)) {
            if(is_first_line) is_first_line = false;
            else{
                size_t c_index = line.find(",", 0);
                double ecg_value = stod(line.substr(c_index+1, line.length()));
                ecg_data.push_back(ecg_value);
            }
        }
        file.close();
    }
    return ecg_data;
}

static const double pi = 3.141592f ;
static const double pi2 = 2.0f * pi ;
static const double s = 3900.111805811;          // Sample rate

void bandpassFilter( double f_hz,           // Filter centre frequency
                     double bw_hz,          // Filter bandwidth
                     const double *x,       // Pointer to input sample block
                     double *y,             // Pointer to output buffer
                     int n                 // Number of samples in sample block
                )
{
    static double x_2 = 0.0f;                    // delayed x, y samples
    static double x_1 = 0.0f;
    static double y_1 = 0.0f;
    static double y_2 = 0.0f;

    static const double f = f_hz / s ;
    static const double bw = bw_hz / s ;

    static const double R = 1 - (3 * bw) ;

    static const double Rsq = R * R ;
    static const double cosf2 = 2 * cos(pi2 * f) ;

    static const double K = (1 - R * cosf2 + Rsq ) / (2 - cosf2) ;

    // static const double a0 = 1.0 - K ;
    // static const double a1 = 2 * (K - R) * cosf2 ;
    // static const double a2 = Rsq - K ;
    // static const double b1 = 2 * R * cosf2 ;
    // static const double b2 = -Rsq ;

    static const double a0 = 1.0f;
    static const double a1 = -1.73356294f;
    static const double a2 = 0.77567951f;
    static const double b0 = 0.11216024f;
    static const double b1 = 0;
    static const double b2 = -0.11216024 ;
    
    for( int i = 0; i < n; ++i)
    {
        // IIR difference equation
        y[i] = (b0 * x[i] + b1 * x_1 + b2 * x_2 
                         - ( a1 * y_1 + a2 * y_2))/a0;

        // shift delayed x, y samples
        x_2 = x_1;                             
        x_1 = x[i];
        y_2 = y_1 ;
        y_1 = y[i];
        //printf("%0.8f\n", y[i]);
    }
}
void diff(double *y, int n){
    double h = sqrt(DBL_EPSILON);
    for(int i = 0; i < n-1; i++) {
        y[i] = y[i+1] - y[i];
        //printf("%0.3f\n", y[i]);
    }
}
int main(){
    vector<double> ecg_data_raw = load_data_from_file("ecg_data/ecg_data_1.csv");
    double x [ecg_data_raw.size()];
    double y [ecg_data_raw.size()] = {};
    copy(ecg_data_raw.begin(), ecg_data_raw.end(), x);
    //get_qrs_indices(ecg_data_raw);
    bandpassFilter(8.660254038f, 5.0f, x, y,  2719);
    //for(int i=0;i<ecg_data_raw.size(); i++) cout<<" x "<< x[i] << " y "<< y[i]<<endl;
    diff(y, ecg_data_raw.size());
    return 0;
}