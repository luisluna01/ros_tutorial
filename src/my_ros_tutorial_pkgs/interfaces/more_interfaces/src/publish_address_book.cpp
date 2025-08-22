#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"


using namespace std::chrono_literals;
using AddressBook = more_interfaces::msg::AddressBook;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher() : Node("address_book_publisher")
  {
    address_book_pub_ = this->create_publisher<AddressBook>("address_book", 10);
    timer_ = this->create_wall_timer(1s, [this]() { this->publish_contact(); });
  }

  void publish_contact() {
    AddressBook msg;

    msg.first_name = "John";
    msg.last_name = "Doe";
    msg.phone_number = "0123456789";
    msg.phone_type = msg.PHONE_TYPE_MOBILE;

    RCLCPP_INFO_STREAM(this->get_logger(),
      "Publishing Contact\nFirst: " << msg.first_name << " Last: " << msg.last_name);

    this->address_book_pub_->publish(msg);
  }


private:
  rclcpp::Publisher<AddressBook>::SharedPtr address_book_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<AddressBookPublisher>();
  
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}