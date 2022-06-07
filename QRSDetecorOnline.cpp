#include <iostream>
#include <fstream>
#include <vector>
#include </home/abuobaidazishan/DevProjects/qrs_detector/utils.h>
using namespace std;

// QRSDetectorOffline class initialisation method.
// :param string ecg_data_path: path to the ECG dataset
// :param bool verbose: flag for printing the results
// :param bool log_data: flag for logging the results
// :param bool plot_data: flag for plotting the results to a file
// :param bool show_plot: flag for showing generated results plot - will not show anything if plot is not generated

// Configuration parameters.


vector<int> get_qrs_indices(vector<float> ecg_raw_data){

    int signal_frequency = 250;  // Set ECG device frequency in samples per second here.
    float filter_lowcut {0.0f};
    float filter_highcut {15.0f};
    float filter_order {1};

    int integration_window {15};  // Change proportionally when adjusting frequency (in samples).

    float findpeaks_limit {0.35};
    float findpeaks_spacing {50};  // Change proportionally when adjusting frequency (in samples).

    int refractory_period{120};  // Change proportionally when adjusting frequency (in samples).
    float qrs_peak_filtering_factor {0.125f};
    float noise_peak_filtering_factor {0.125f};
    float qrs_noise_diff_weight  {0.25};

    // Loaded ECG data.
    //float ecg_data_raw []{};

    // Measured and calculated values.
    vector <float> filtered_ecg_measurements;
    vector <float> differentiated_ecg_measurements;
    vector <float> squared_ecg_measurements;
    vector <float> integrated_ecg_measurements;
    vector <int> detected_peaks_indices;
    vector <float> detected_peaks_values;

    float qrs_peak_value {0.0f};
    float noise_peak_value {0.0f};
    float threshold_value = {0.0f};

    // Detection results.
    // qrs_peaks_indices = np.array([], dtype=int)
    // noise_peaks_indices = np.array([], dtype=int)

    // Final ECG data and QRS detection results array - samples with detected QRS are marked with 1 value.
    //ecg_data_detected = None

    return detected_peaks_indices;
}

vector<float> load_data_from_file(const char* path){
    std::ifstream file(path);
    vector<float> ecg_data;
    if (file.is_open()) {
        string line;
        bool is_first_line = true;
        while (std::getline(file, line)) {
            if(is_first_line) is_first_line = false;
            else{
                size_t c_index = line.find(",", 0);
                float ecg_value = stof(line.substr(c_index+1, line.length()));
                ecg_data.push_back(ecg_value);
            }
        }
        file.close();
    }
    return ecg_data;
}

int main(){
    vector<float> ecg_data_raw = load_data_from_file("ecg_data/ecg_data_1.csv");
    get_qrs_indices(ecg_data_raw);
    return 0;
}