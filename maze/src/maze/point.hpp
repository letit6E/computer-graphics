struct Point {
    double x, y;

    bool operator<(const Point &other) const {
        if (x == other.x)
            return y < other.y;
        else
            return x < other.x;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    bool operator<=(const Point &other) const {
        return (*this < other) || (*this == other);
    }

    bool operator>(const Point &other) const {
        return !(*this <= other);
    }

    bool operator>=(const Point &other) const {
        return !(*this < other);
    }
};