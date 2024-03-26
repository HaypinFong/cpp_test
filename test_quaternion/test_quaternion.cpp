#include<iostream>
#include"tf/LinearMath/Transform.h"
#include"tf/transform_datatypes.h"
#include<vector>
using namespace std;
#define PI 3.1415926
int main(int argc,char **argv){
    tf::Transform mytf;
    mytf.setOrigin( tf::Vector3(0.0,0.0,0.0) );
    mytf.setRotation( tf::createQuaternionFromYaw(-1.5*PI) );
    cout<<tf::getYaw( mytf.getRotation() )<<" .vs. "<<PI/2<<endl;
    mytf.setRotation( tf::createQuaternionFromYaw(1.5*PI) );
    cout<<tf::getYaw( mytf.getRotation() )<<" .vs. "<<-1*PI/2<<endl;
    mytf.setRotation( tf::createQuaternionFromYaw(0.99*PI) );
    cout<<tf::getYaw( mytf.getRotation() )<<endl;
    mytf.setRotation( tf::createQuaternionFromYaw(-0.99*PI) );
    cout<<tf::getYaw( mytf.getRotation() )<<endl;   // Yaw()确实在[-PI,PI]之间

    int arr[]={3,1,4,1,5,9};
    size_t index(2);
    cout<<arr[index]<<endl;

    std::vector<int> arr2={3,1,4,1,5,9};
    cout<<arr2[index]<<endl;

    cout<<( (arr2.size()>2.0f)?"true":"false" )<<endl;

    double num1(1<<30),num2(1<<29);
    cout<<num1<<' '<<num2<<' '<<num1+num2<<endl;

    std::vector<int> varr(3,-1),varr2(10,3);
    varr.insert(varr.end(),varr2.begin(),varr2.begin()+varr2.size()/4);
    for(int &i:varr) cout<<i<<' ';
    cout<<endl;

    double num3(1e-3);
    float num4(num3);
    cout<<num4<<endl;
    return 0;
}