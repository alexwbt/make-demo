#include <iostream>

#include <vec2.pb.h>

void printMessage(const google::protobuf::Message& message)
{
    const auto *descriptor = message.GetDescriptor();
    const auto *reflection = message.GetReflection();
    std::cout << "\n";
    for (int i = 0; i < descriptor->field_count(); ++i)
    {
        const auto *field = descriptor->field(i);
        std::cout << field->name() << "(" << field->type_name() << ")" << ": ";
        switch (field->type())
        {
        case google::protobuf::FieldDescriptor::TYPE_FLOAT:
            std::cout << reflection->GetFloat(message, field) << "\n";
            break;
        case google::protobuf::FieldDescriptor::TYPE_DOUBLE:
            std::cout << reflection->GetDouble(message, field) << "\n";
            break;
        case google::protobuf::FieldDescriptor::TYPE_INT32:
            std::cout << reflection->GetInt32(message, field) << "\n";
            break;
        case google::protobuf::FieldDescriptor::TYPE_INT64:
            std::cout << reflection->GetInt64(message, field) << "\n";
            break;
        default:
            break;
        }
    }
}

int main()
{
    proto::Vec2f vec2;
    vec2.set_x(123);
    vec2.set_y(321);

    printMessage(vec2);

    std::string serialized_string;
    vec2.SerializeToString(&serialized_string);

    proto::Vec2f message;
    message.ParseFromString(serialized_string);

    printMessage(message);


    return 0;
}
