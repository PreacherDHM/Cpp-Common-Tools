#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#define INT256_SIZE 256

/* 
 * The int256 is an array of type *char* and has a lanth of *256*.
 * The int256 is able to hold the hash of of an **ETH** NFT */
typedef struct i256 {
    char data[256];
    i256(char *Data) {for(int i = 0; i < 256; i++) { data[i] = Data[i]; }};
    
    i256 operator = (const i256& obj){ i256 t((char*)obj.data); return t; }
    
} int256;

// Vector 2
typedef struct fv2 {
    float x, y;
    fv2(float x,float y) : x(x),y(y) {}; 

    //Operaters
    fv2 operator = (const fv2& obj) { fv2 tmp(obj.x,obj.y); return tmp; }
    fv2 operator + (const fv2& obj) { fv2 tmp(x + obj.x, y + obj.y); return tmp; }
    fv2 operator - (const fv2& obj) { fv2 tmp(x - obj.x, y - obj.y); return tmp; }
    fv2 operator * (const fv2& obj) { fv2 tmp(x * obj.x, y * obj.y); return tmp; }
    fv2 operator / (const fv2& obj) { fv2 tmp(x / obj.x, y / obj.y); return tmp; }

} vec2;

// Vector 3
typedef struct fv3 {
    float x, y, z;
    fv3(float x,float y, float z) : x(x),y(y),z(z) {}; 

    //Operaters
    fv3 operator = (const fv3& obj) { fv3 tmp(obj.x,obj.y,obj.z); return tmp; }
    fv3 operator + (const fv3& obj) { fv3 tmp(x + obj.x, y + obj.y,z + obj.z); return tmp; }
    fv3 operator - (const fv3& obj) { fv3 tmp(x - obj.x, y - obj.y,z - obj.z); return tmp; }
    fv3 operator * (const fv3& obj) { fv3 tmp(x * obj.x, y * obj.y,z * obj.z); return tmp; }
    fv3 operator / (const fv3& obj) { fv3 tmp(x / obj.x, y / obj.y,z / obj.z); return tmp; }

} vec3;
#endif
