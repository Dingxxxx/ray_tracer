#ifndef SPHEREH
#define SPHEREH

#include "Hitable.h"

class sphere: public hitable{
    public:
        sphere() {}
        // 构造函数：位置，距离
        sphere(vec3 cen, float r): center(cen), radius(r) {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
    vec3  oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b*b - a*c;
    // 按照距离远近着色
    if (discriminant > 0){
        float temp = (- b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (- b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min){
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif