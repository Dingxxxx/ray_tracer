#include <iostream>
#include "libs/Sphere.h"
#include "libs/Hitablelist.h"
#include "libs/Camera.h"
#include "float.h"
#include "libs/Material.h"
using namespace std;



vec3 color(const ray& r, hitable *world, int depth){
    hit_record rec;
    if (world->hit(r, 0.001, MAXFLOAT, rec)){
        // 物体
        ray scattered;
        vec3 attenutation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenutation, scattered)) {
            // 反射次数在 50 次
            return attenutation * color(scattered, world, depth+1);
        }
        else {
            //cout << "50次反射" << "\n";
            return vec3(0,0,0);
        }
    }
    else {
        // 背景色
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main(){
    int nx = 200; // 图像长
    int ny = 100; // 
    int ns = 100; // 随机采样数
    cout << "P3\n" << nx << " " << ny << "\n255\n";
    hitable *list[4];
    list[0] = new sphere(vec3(0 ,0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    // 场景
    hitable *world = new hitable_list(list, 4);
    // 相机
    camera cam;
    for (int j = ny-1; j >=0; j--){
        for (int i = 0; i < nx; i++){
            vec3 col(0, 0, 0);
            for (int s=0; s < ns; s++) {
                // 在一个像素内随机偏移
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.point_at_parameter(2.0);
                //cout << color(r, world, 0)[0] <<' ' << color(r, world, 0)[1] << ' '<< color(r, world, 0)[2] <<"\n";
                //vec3 tmpc = color(r, world, 0);
                col = col + color(r, world, 0);
            }
            // 开平方增加亮度
            col = col / float(ns);
            int ir = int(255.99*sqrt(col[0]));
            int ig = int(255.99*sqrt(col[1]));
            int ib = int(255.99*sqrt(col[2]));
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
