#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>

class OpenCVNode : public rclcpp::Node {
public:
  OpenCVNode() : Node("opencv_node") {
    image_subscriber_ = create_subscription<sensor_msgs::msg::Image>(
      "image",
      10,
      [this](const sensor_msgs::msg::Image::SharedPtr msg) {
        processImage(msg);
      }
    );
  }

private:
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;

  void processImage(const sensor_msgs::msg::Image::SharedPtr msg) {
    try {
      cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, "bgr8");
      cv::imshow("OpenCV Node", cv_ptr->image);
      cv::waitKey(1);
    } catch (const cv_bridge::Exception& e) {
      RCLCPP_ERROR(get_logger(), "Error converting image: %s", e.what());
    }
  }
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OpenCVNode>());
  rclcpp::shutdown();
  return 0;
}
