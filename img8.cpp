#include <iostream>
#include "libs/Sphere.h"
#include "libs/Hitablelist.h"
#include "libs/Camera.h"
#include "float.h"
using namespace std;

// 生成漫反射射方向
// Lambertian
vec3 random_in_unit_sphere() {
    vec3 p;
    // 在单位立方体内随机取一个在单位球内的点
    do {
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
    } while (dot(p, p) >= 1);
    return p;
}

vec3 color(const ray& r, hitable *world){
    hit_record rec;
    if (world->hit(r, 0.0, MAXFLOAT, rec)){
        // 物体
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5*color( ray(rec.p, target-rec.p), world);
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
    hitable *list[2];
    list[0] = new sphere(vec3(0 ,0, -1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    // 场景
    hitable *world = new hitable_list(list, 2);
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
                col = col + color(r, world);
            }
            col = col / float(ns);
            int ir = int(255.99*sqrt(col[0]));
            int ig = int(255.99*sqrt(col[1]));
            int ib = int(255.99*sqrt(col[2]));
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }

}