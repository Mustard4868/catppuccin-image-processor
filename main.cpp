#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <limits>

// Function to calculate the closest color in the palette
cv::Vec3b closestColor(const cv::Vec3b& pixel, const std::vector<cv::Vec3b>& palette) {
    double minDistance = std::numeric_limits<double>::max();
    cv::Vec3b closestColor;

    for (const auto& color : palette) {
        // Compute Euclidean distance
        double distance = std::sqrt(
            std::pow(pixel[0] - color[0], 2) +  // Blue
            std::pow(pixel[1] - color[1], 2) +  // Green
            std::pow(pixel[2] - color[2], 2)    // Red
        );

        if (distance < minDistance) {
            minDistance = distance;
            closestColor = color;
        }
    }
    return closestColor;
}

std::vector<cv::Vec3b> getPalette(const std::string& paletteName) {
    if (paletteName == "latte") {
        return {
            {120, 138, 220},    // Rosewater
            {120, 120, 221},    // Flamingo
            {203, 118, 234},    // Pink
            {239, 57, 136},     // Mauve
            {57, 15, 210},      // Red
            {83, 69, 230},      // Maroon
            {11, 100, 254},     // Peach
            {29, 142, 223},     // Yellow
            {43, 160, 64},      // Green
            {153, 146, 23},     // Teal
            {229, 165, 4},      // Sky
            {181, 159, 32},     // Sapphire
            {245, 102, 30},     // Blue
            {253, 135, 114},    // Lavender
            {105, 79, 76},      // Text
            {119, 95, 92},      // Subtext 1
            {133, 111, 108},    // Subtext 0
            {147, 127, 124},    // Overlay 2
            {161, 143, 140},    // Overlay 1
            {176, 160, 156},    // Overlay 0
            {190, 176, 172},    // Surface 2
            {204, 192, 188},    // Surface 1
            {218, 208, 204},    // Surface 0
            {245, 241, 239},    // Base
            {239, 233, 230},    // Mantle
            {232, 224, 220}     // Crust
        };
    }
    else if (paletteName == "frappe") {
        return {
            {207, 213, 242},    // Rosewater
            {190, 190, 238},    // Flamingo
            {228, 184, 244},    // Pink
            {230, 158, 202},    // Mauve
            {132, 130, 231},    // Red
            {156, 153, 234},    // Maroon
            {118, 159, 239},    // Peach
            {144, 200, 229},    // Yellow
            {137, 209, 166},    // Green
            {190, 200, 129},    // Teal
            {219, 209, 153},    // Sky
            {220, 193, 133},    // Sapphire
            {238, 170, 140},    // Blue
            {241, 187, 186},    // Lavender
            {245, 208, 198},    // Text
            {226, 191, 181},    // Subtext 1
            {206, 173, 165},    // Subtext 0
            {187, 156, 148},    // Overlay 2
            {167, 139, 131},    // Overlay 1
            {148, 121, 115},    // Overlay 0
            {128, 104, 98},     // Surface 2
            {109, 87, 81},      // Surface 1
            {89, 69, 65},       // Surface 0
            {70, 52, 48},       // Base
            {60, 44, 41},       // Mantle
            {52, 38, 35}        // Crust
        };
    }
    else if (paletteName == "macchiato") {
        return {
            {120, 138, 244},    // Rosewater
            {198, 198, 240},    // Flamingo
            {230, 189, 245},    // Pink
            {246, 160, 198},    // Mauve
            {150, 135, 237},    // Red
            {160, 153, 238},    // Maroon
            {127, 169, 245},    // Peach
            {159, 212, 238},    // Yellow
            {149, 218, 166},    // Green
            {202, 213, 139},    // Teal
            {227, 215, 145},    // Sky
            {228, 196, 125},    // Sapphire
            {244, 173, 138},    // Blue
            {248, 189, 183},    // Lavender
            {245, 211, 202},    // Text
            {224, 192, 184},    // Subtext 1
            {203, 173, 165},    // Subtext 2
            {183, 154, 147},    // Overlay 2
            {162, 135, 128},    // Overlay 1
            {141, 115, 110},    // Overlay 0
            {120, 96, 91},      // Surface 2
            {100, 77, 73},      // Surface 1
            {79, 58, 54},       // Surface 0
            {58, 39, 36},       // Base
            {48, 32, 30},       // Mantle
            {38, 25, 24}        // Crust
        };
    }
    else if (paletteName == "moccha") {
        return {
            {220, 224, 245},    // Rosewater
            {205, 205, 242},    // Flamingo
            {231, 194, 245},    // Pink
            {247, 194, 203},    // Mauve
            {168, 139, 243},    // Red
            {172, 160, 235},    // Maroon
            {135, 179, 250},    // Peach
            {175, 226, 249},    // Yellow
            {161, 227, 166},    // Green
            {213, 226, 148},    // Teal
            {235, 220, 137},    // Sky
            {236, 199, 116},    // Sapphire
            {250, 180, 137},    // Blue
            {254, 190, 180},    // Lavender
            {244, 214, 205},    // Text
            {222, 194, 186},    // Subtext 1
            {200, 173, 166},    // Subtext 2
            {178, 153, 147},    // Overlay 2
            {156, 132, 127},    // Overlay 1
            {134, 112, 108},    // Overlay 0
            {112, 91, 88},      // Surface 2
            {90, 71, 69},       // Surface 1
            {68, 50, 49},       // Surface 0
            {46, 30, 30},       // Base
            {37, 24, 24},       // Mantle
            {27, 17, 17}        // Crust
        };
    }
    else {
        throw std::invalid_argument("Unknown palette: " + paletteName);
    }
}

// Function to process the image and reduce colors to the palette
void reduceImageColors(const std::string& inputPath, const std::string& outputPath, const std::vector<cv::Vec3b>& palette) {
    // Load the image
    cv::Mat image = cv::imread(inputPath);
    if (image.empty()) {
        std::cerr << "Error: Could not load the image at " << inputPath << std::endl;
        return;
    }

    // Clone the image for output
    cv::Mat reducedImage = image.clone();

    // Iterate over every pixel in the image
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            // Get the original pixel color (BGR format in OpenCV)
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            // Find the closest color in the palette
            cv::Vec3b newColor = closestColor(pixel, palette);

            // Set the pixel in the reduced image
            reducedImage.at<cv::Vec3b>(y, x) = newColor;
        }
        // Debug progress (optional)
        if (y % 50 == 0) {
            std::cout << "Processing row " << y << "/" << image.rows << std::endl;
        }
    }

    // Save the processed image
    if (!cv::imwrite(outputPath, reducedImage)) {
        std::cerr << "Error: Could not save the image to " << outputPath << std::endl;
        return;
    }
    std::cout << "Processed image saved to: " << outputPath << std::endl;
}

int main(int argc, char* argv[]) {
    // Check command-line arguments
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_image_path> --palette <palette_name>" << std::endl;
        return -1;
    }

    std::string inputPath = argv[1];
    std::string paletteFlag = argv[2];
    if (paletteFlag != "--palette") {
        std::cerr << "Error: Invalid flag " << paletteFlag << std::endl;
        return -1;
    }

    std::string paletteName = argv[3];
    size_t pos = inputPath.find_last_of("/\\");
    std::string outputPath;
    if (pos != std::string::npos) {
        outputPath = inputPath.substr(0, pos + 1) + paletteName + "_" + inputPath.substr(pos + 1);
    } else {
        outputPath = paletteName + "_" + inputPath;
    }

    std::vector<cv::Vec3b> palette;
    try {
        palette = getPalette(paletteName);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // Reduce image colors
    reduceImageColors(inputPath, outputPath, palette);

    return 0;
}
