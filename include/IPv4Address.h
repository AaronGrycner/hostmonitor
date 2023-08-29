//
// Created by aaron on 8/29/23.
//

#ifndef YOSHIMIWRT_IPV4ADDRESS_H
#define YOSHIMIWRT_IPV4ADDRESS_H


class IPv4Address {
private:
    std::string address{};

public:
    IPv4Address()=default;
    explicit IPv4Address(std::string addr) : address(std::move(addr)) {}
    [[nodiscard]] std::string to_string() const { return address; }

    bool operator==(const IPv4Address &rhs) const {
        if (address == rhs.address) {
            return true;
        }
        return false;
    }

    bool operator!=(const IPv4Address &rhs) const {
        if (address != rhs.address) {
            return true;
        }
        return false;
    }

    IPv4Address& operator =(const std::string &rhs) {
        address = rhs;
        return *this;
    }
};


#endif //YOSHIMIWRT_IPV4ADDRESS_H
