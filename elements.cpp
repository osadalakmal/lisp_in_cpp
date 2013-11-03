
#include <elements.h>

std::ostream& operator<<(std::ostream& out, std::shared_ptr<Elem> elem) {
    if (elem->type == DATA_TYPE::PROC) {
        out << "[";
        for (auto i = 0; i < elem->valExp.size(); i++) {
            out << elem->valExp[i];
            if (i != (elem->valExp.size()-1)) {
                out << " , ";
            }
        }
        out << "]";
    } else if (elem->type == DATA_TYPE::INT) {
        out << elem->valInt;
    }  else if (elem->type == DATA_TYPE::DOUBLE) {
        out << elem->valDbl;
    }  else if (elem->type == DATA_TYPE::STRING) {
        out << "\"" << elem->valStr << "\"";
    } else {
        out << convertToStr(elem->type);
    }
    return out;
}
