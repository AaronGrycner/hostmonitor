//
// Created by aaron on 8/29/23.
//

#ifndef YOSHIMIWRT_HWADDRESS_H
#define YOSHIMIWRT_HWADDRESS_H


class HWAddress {
private:
    std::string address{};

public:
    HWAddress()=default;
    explicit HWAddress(std::string addr) : address(std::move(addr)) {}
    [[nodiscard]] std::string to_string() const { return address; }

    bool operator ==(const HWAddress &rhs) const {
        if (address == rhs.address) {
            return true;
        }
        return false;
    }

    bool operator !=(const HWAddress &rhs) const {
        if (address != rhs.address) {
            return true;
        }
        return false;
    }

    HWAddress& operator =(const std::string &rhs) {
        address = rhs;
        return *this;
    }
};


#endif //YOSHIMIWRT_HWADDRESS_H
