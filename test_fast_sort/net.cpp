#include<iostream>
#include<math>
// 二维平面下的点是否在循转的矩形框内，
void roll_point(float &x,float &y,float yaw){
    float x_new(x),y_new(y);
    y_new = (y-x*std::tan(yaw))*std::cos(yaw);
    x_new = x/std::cos(yaw)+y_new*std::tan(yaw);
    // 其实循转矩阵*[x,y]T直接返回旋转后向量[x',y']T，R*(Trans+Y)
    x = x_new;
    y = y_new;
}
bool point_in_trans_matrix(float x,float y,float H, float W,float yaw,float px,float py){
    // 将矩形循转yaw，简化矩形
    float x_new(x),y_new(y);
    roll_point(x_new,y_new,yaw);
    float px_new(px),py_new(py);
    roll_point(px_new,py_new);
    // 长宽不变，判断点在矩形内：
    return (px_new-x_new+H/2.0)*(px_new-x_new-H/2.0)<0 &&
        (py_new-y_new+W/2.0)*(py_new-y_new-W/2.0)<0;
}