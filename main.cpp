#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <time.h>

using namespace std;

struct neuron {
    double value;
    double error;
    void act() {
        value = (1 / (1 + pow(2.71828, -value)));
    }
};

class network {
public:
    int layers;
    neuron** neurons;
    double*** weights;
    int* size;
    int threadNum;

    double sigm_pro(double x) {
        if ((fabs(x - 1) < 1e-9) || (fabs(x) < 1e-9)) return 0.0;
        double res = x * (1.0 - x);
        return res;
    }

    double predict(double x) {
        if (x >= 0.8) return 1;
        else return 0;
    }

    void set_layers(int n, int* p) {
        srand(time(0));
        layers = n;
        neurons = new neuron* [n];
        weights = new double** [n - 1];
        size = new int [n];

        for (int i = 0; i < n; i++) {
            size[i] = p[i];
            neurons[i] = new neuron [p[i]];
            if (i < n - 1) {
                weights[i] = new double* [p[i + 1]];
                for (int j = 0; j < p[i]; j++) {
                    weights[i][j] = new double [p[i + 1]];
                    for (int k = 0; k < p[i + 1]; k++) {
                        weights[i][j][k] = (rand() % 100) * 0.01 / size[i];
                    }
                }
            }
        }
    }

    void set_input(double* p) {
        for (int i = 0; i < size[0]; i++) {
            neurons[0][i].value = p[i]; 
        }
    }

    void show() {
        setlocale(LC_ALL, "ru");
        cout << "Архитектура нейронной сети: ";
        for (int i = 0; i < layers; i ++) {
            cout << size[i];
            if (i < layers - 1) {
                cout << " - ";
            }
        }
        cout << "\n";
        for (int i = 0; i < layers; i++) {
            cout << "\n#Слой " << i + 1 << "\n\n";
            for (int j = 0; j < size[i]; j++) {
                cout << "Нейрон #" << j + 1 << "\n";
                cout << "Згачение #" << neurons[i][j].value << "\n";
                if (i < layers - 1) {
                    cout << "Веса: \n";
                    for (int k = 0; k < size[i + 1]; k++) {
                        cout << "#" << k + 1 << ": ";
                        cout << weights[i][j][k] << "\n";
                    }
                }
            }
        }
    }

    void LayersCleaner(int LayerNumber, int start, int stop) {
        for (int i = start; i < stop; i++) {
            neurons[LayerNumber][i].value = 0;
        }
    }

    void ForwardFeeder(int LayerNumber, int start, int stop) {
        for (int j = start; j < stop; j++) {
            for (int k = 0; k < size[LayerNumber - 1]; k++) {
                neurons[LayerNumber][j].value += neurons[LayerNumber - 1][k].value * weights[LayerNumber][k][j];
            }
            neurons[LayerNumber][j].act();
        }
    }

    double* ForwardFeed() {
        for (int i = 0; i < layers; i++) {
            LayersCleaner(i , 0, size[i]);
            ForwardFeeder(i, 0, size[i]);
        }
        double* pred = new double[size[layers - 1]];
        for (int i = 0; i < size[layers - 1]; i++) {
            pred[i] = neurons[layers - 1][i].value;
        }
        return pred;
    }

    void ErrorCounter(int LayerNumber, int start, int stop, double* pred, double* rresult, double lr) {
        if (LayerNumber == layers - 1) {
            for (int j = start; j < stop; j++) {
                if (neurons[layers - 1][j].value != rresult[j]) {
                    neurons[layers - 1][j].error = -pow(neurons[layers - 1][j].value, 2);
                } else {
                    neurons[layers - 1][j].error = 1.0 - neurons[layers - 1][j].value;
                }
            }
        } else {
            for (int j = start; j < stop; j++) {
                double error = 0.0;
                for (int k = 0; k < size[LayerNumber + 1]; k++) {
                    error += neurons[LayerNumber + 1][k].error * weights[LayerNumber][j][k];
                }
                neurons[LayerNumber][j].error = error;
            }
        }
    }

    void WeightsUpdater(int start, int stop, int LayerNum, int lr) {
        int i = LayerNum;
        for (int j = start; j < stop; j++) {
            for (int k = 0; k < size[i + 1]; k++) {
                weights[i][j][k] += lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
            }
        }
    }

    void BackPropogation(double* prediction, double* rresult, int lr) {
        for (int i = layers - 1; i > 0; i--) {
            if (i == layers - 1) {
                for (int j = 0; j < size[i]; j++) {
                    if (prediction[j] != rresult[j]) {
                        neurons[i][j].error = -pow(neurons[i][j].value, 2);
                    } else {
                        neurons[i][j].error = 1 - neurons[i][j].value;
                    }
                }
            } else {
                for (int j = 0; j < size[i]; j++) {
                    double error = 0.0;
                    for (int k = 0; k < size[i + 1]; k++) {
                        error += neurons[i + 1][k].error * weights[i][j][k];
                    }
                    neurons[i][j].error = error;
                }
            }
        }
    }

    int SaveWeights() {
        ofstream fout;
        fout.open("weights.txt");
        for (int i = 0; i < layers; i++) {
            if ( i < layers - 1) {
                for (int j = 0; j < size[i]; j++) {
                    for (int k = 0; k < size[k + 1]; k++) {
                        fout << weights[i][j][k] << " ";
                    }
                }
            }
        }
        fout.close();
        return 1;
    }    
};

int main() {

    double* given = new double [360 * 360];
    double* answer = new double [360 * 360];
    int count = 0;
    for (int i = 0; i <= 360; i++) {
        for (int j = 0; j <= 360; j++) {
            double i_rad = i * 3.14 / 180;
            double j_rad = j * 3.14 / 180;

            double x = 50 * cos(i_rad) + 50 * cos(i_rad + j_rad);
            double y = 50 * sin(i_rad) + 50 * sin(i_rad + j_rad);

            given[count] = double(x / 100);
            given[count + 1] = double(y / 100);

            answer[count] = double(i / 360);
            answer[count + 1] = double(j / 360);

            count += 2;
        }
    }

    network net;
    int layers[] = {2, 16, 2};
    net.set_layers(3, layers);
    bool study;
    cout << "To study?(0/1) >> ";
    cin >> study;
    if (study) {
        double percentRight = 0;
        int epoch = 1;
        while (percentRight < 98) {
            cout << "Epoch: " << epoch << "\n";
            double rightAnswers = 0;
            for (int i = 0; i < 360 * 360; i += 2) {
                double input[] = {given[i], given[i + 1]};
                net.set_input(input);
                double* result = net.ForwardFeed();
                if (result[0] != answer[i] and result[1] != answer[i + 1]) {
                    double rresult[] = {answer[i], answer[i + 1]};
                    net.BackPropogation(result, rresult, 0.25);
                } else {
                    rightAnswers++;
                }
            }
            percentRight = rightAnswers / (360 * 360) * 100;
            cout << "Right answers: " << percentRight << "%\n";
            epoch++;
        }
        net.SaveWeights();
    }
    double coord[2];
    cout << "Enter coord >> "; cin >> coord[0] >> coord[1];
    coord[0] /= 100;
    coord[1] /= 100;
    net.set_input(coord);
    double* ans = net.ForwardFeed();
    cout << "Deg: " << ans[0] * 360 << " " << ans[1] * 360 << "\n";

    return 0;
}