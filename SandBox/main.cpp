#include "AET.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main(int argc, char **argv) {


    vector<float> input_coordinates;

    input_coordinates.push_back((float)2.0);
	input_coordinates.push_back((float)3.0);

    input_coordinates.push_back((float)7.0);
	input_coordinates.push_back((float)1.0);

    input_coordinates.push_back((float)13.0);
	input_coordinates.push_back((float)5.0);

    input_coordinates.push_back((float)13.0);
	input_coordinates.push_back((float)11.0);

    input_coordinates.push_back((float)7.0);
	input_coordinates.push_back((float)7.0);

    input_coordinates.push_back((float)1.0);
	input_coordinates.push_back((float)9.0);

    PoliFill(input_coordinates);
    return 0;
}
