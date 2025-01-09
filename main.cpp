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
    if (paletteName == "macchiato") {
        return {
            {120, 138, 244}, // Rosewater
            {198, 198, 240}, // Flamingo
            {230, 189, 245}, // Pink
            {246, 160, 198}, // Mauve
            {150, 135, 237}, // Red
            {160, 153, 238}, // Maroon
            {127, 169, 245}, // Peach
            {159, 212, 238}, // Yellow
            {149, 218, 166}, // Green
            {202, 213, 139}, // Teal
            {227, 215, 145}, // Sky
            {228, 196, 125}, // Sapphire
            {244, 173, 138}, // Blue
            {248, 189, 183}, // Lavender
            {245, 211, 202}, // Text
            {224, 192, 184}, // Subtext 1
            {203, 173, 165}, // Subtext 2
            {183, 154, 147}, // Overlay 2
            {162, 135, 128}, // Overlay 1
            {141, 115, 110}, // Overlay 0
            {120, 96, 91},   // Surface 2./
            {100, 77, 73},   // Surface 1
            {79, 58, 54},    // Surface 0
            {58, 39, 36},    // Base
            {48, 32, 30},    // Mantle
            {38, 25, 24}     // Crust
        };
    } else if (paletteName == "solarized") {
        return {
            {54, 43, 0},      // Base03 (BGR format)
            {66, 54, 7},      // Base02
            {117, 110, 88},   // Base01
            {131, 123, 101},  // Base00
            {150, 148, 131},  // Base0
            {161, 161, 147},  // Base1
            {227, 246, 253},  // Base3
            {0, 137, 181}     // Yellow
        };
    } else {
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
