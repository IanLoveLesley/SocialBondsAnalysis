#ifndef SOCIALBONDSANALYSIS_MYADJMAT_H
#define SOCIALBONDSANALYSIS_MYADJMAT_H

template <typename T, T diag_default_value>
class MyAdjMat
{
// 通过 typedef 提高代码可读性
typedef T* Ptrlevel1;
typedef T** Ptrlevel2;
public:
    MyAdjMat(int sideLength);
    ~MyAdjMat();
    // 不允许无参数构造；暂时不允许拷贝，这个以后可能会开发
    MyAdjMat() = delete;
    MyAdjMat(const MyAdjMat&) = delete;
    MyAdjMat& operator=(const MyAdjMat&) = delete;

    inline const int& getSideLength() const {return sideLength}
    inline int& getSideLength() = delete;
    // 拷贝开销 vs 解引用开销
    void setSideLength(int sideLength) {this->sideLength = sideLength;}
private:
    int sideLength;
    Ptrlevel2 memory;
};

#endif //SOCIALBONDSANALYSIS_MYADJMAT_H