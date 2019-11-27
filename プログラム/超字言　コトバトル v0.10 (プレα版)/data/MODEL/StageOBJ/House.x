xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 448;
 -54.50717;29.01906;47.32374;,
 -56.51864;29.01906;47.32374;,
 -56.51864;29.01906;-45.59203;,
 -54.50717;29.01906;-45.59203;,
 -54.50717;29.01906;-45.59203;,
 -56.51864;29.01906;-45.59203;,
 -56.51864;31.03053;-45.59203;,
 -54.50717;31.03053;-45.59203;,
 -54.50717;31.03053;-45.59203;,
 -56.51864;31.03053;-45.59203;,
 -56.51864;31.03053;47.32374;,
 -54.50717;31.03053;47.32374;,
 -54.50717;31.03053;47.32374;,
 -56.51864;31.03053;47.32374;,
 -56.51864;29.01906;47.32374;,
 -54.50717;29.01906;47.32374;,
 -56.51864;29.01906;47.32374;,
 -56.51864;31.03053;47.32374;,
 -56.51864;31.03053;-45.59203;,
 -56.51864;29.01906;-45.59203;,
 -54.50717;31.03053;47.32374;,
 -54.50717;29.01906;47.32374;,
 -54.50717;29.01906;-45.59203;,
 -54.50717;31.03053;-45.59203;,
 -54.50717;16.07212;47.32374;,
 -56.51864;16.07212;47.32374;,
 -56.51864;16.07212;-45.59203;,
 -54.50717;16.07212;-45.59203;,
 -54.50717;16.07212;-45.59203;,
 -56.51864;16.07212;-45.59203;,
 -56.51864;18.08359;-45.59203;,
 -54.50717;18.08359;-45.59203;,
 -54.50717;18.08359;-45.59203;,
 -56.51864;18.08359;-45.59203;,
 -56.51864;18.08359;47.32374;,
 -54.50717;18.08359;47.32374;,
 -54.50717;18.08359;47.32374;,
 -56.51864;18.08359;47.32374;,
 -56.51864;16.07212;47.32374;,
 -54.50717;16.07212;47.32374;,
 -56.51864;16.07212;47.32374;,
 -56.51864;18.08359;47.32374;,
 -56.51864;18.08359;-45.59203;,
 -56.51864;16.07212;-45.59203;,
 -54.50717;18.08359;47.32374;,
 -54.50717;16.07212;47.32374;,
 -54.50717;16.07212;-45.59203;,
 -54.50717;18.08359;-45.59203;,
 -54.50717;-0.73692;47.32374;,
 -56.51864;-0.73692;47.32374;,
 -56.51864;-0.73692;-45.59203;,
 -54.50717;-0.73692;-45.59203;,
 -54.50717;-0.73692;-45.59203;,
 -56.51864;-0.73692;-45.59203;,
 -56.51864;1.27455;-45.59203;,
 -54.50717;1.27455;-45.59203;,
 -54.50717;1.27455;-45.59203;,
 -56.51864;1.27455;-45.59203;,
 -56.51864;1.27455;47.32374;,
 -54.50717;1.27455;47.32374;,
 -54.50717;1.27455;47.32374;,
 -56.51864;1.27455;47.32374;,
 -56.51864;-0.73692;47.32374;,
 -54.50717;-0.73692;47.32374;,
 -56.51864;-0.73692;47.32374;,
 -56.51864;1.27455;47.32374;,
 -56.51864;1.27455;-45.59203;,
 -56.51864;-0.73692;-45.59203;,
 -54.50717;1.27455;47.32374;,
 -54.50717;-0.73692;47.32374;,
 -54.50717;-0.73692;-45.59203;,
 -54.50717;1.27455;-45.59203;,
 152.20260;93.38691;-37.23863;,
 15.96184;93.38691;-37.23863;,
 84.08222;184.63280;-37.23863;,
 84.08222;184.63280;45.01351;,
 15.96184;93.38692;45.01351;,
 152.20260;93.38692;45.01351;,
 152.20270;0.56702;45.01351;,
 15.96189;0.56702;45.01351;,
 15.96189;0.56702;-37.23863;,
 152.20270;0.56702;-37.23863;,
 15.96184;93.38692;45.01351;,
 84.08222;184.63280;45.01351;,
 152.20260;93.38692;45.01351;,
 84.08222;184.63280;45.01351;,
 152.20270;0.56702;-37.23863;,
 15.96189;0.56702;-37.23863;,
 15.96189;0.56702;45.01351;,
 152.20270;0.56702;45.01351;,
 183.62969;73.24676;-47.06567;,
 175.88582;69.12787;-47.06567;,
 84.36981;187.53476;-47.06566;,
 84.36981;191.65368;-47.06566;,
 84.36981;191.65368;-47.06566;,
 84.36981;187.53476;-47.06566;,
 84.36981;187.53476;54.84054;,
 84.36981;191.65368;54.84054;,
 84.36981;191.65368;54.84054;,
 84.36981;187.53476;54.84054;,
 175.88582;69.12787;54.84054;,
 183.62969;73.24676;54.84054;,
 183.62969;73.24676;54.84054;,
 175.88582;69.12787;54.84054;,
 175.88582;69.12787;-47.06567;,
 183.62969;73.24676;-47.06567;,
 175.88582;69.12787;-47.06567;,
 175.88582;69.12787;54.84054;,
 84.36981;187.53476;54.84054;,
 84.36981;187.53476;-47.06566;,
 183.62969;73.24676;54.84054;,
 183.62969;73.24676;-47.06567;,
 84.36981;191.65368;-47.06566;,
 84.36981;191.65368;54.84054;,
 84.36981;187.53476;54.84054;,
 84.36981;191.65368;54.84054;,
 -55.48333;71.41953;54.84054;,
 -46.72452;70.95510;54.84054;,
 -46.72452;70.95510;54.84054;,
 -55.48333;71.41953;54.84054;,
 -55.48333;71.41953;-47.06567;,
 -46.72452;70.95510;-47.06567;,
 -46.72452;70.95510;-47.06567;,
 -55.48333;71.41953;-47.06567;,
 84.36981;191.65368;-47.06566;,
 84.36981;187.53476;-47.06566;,
 84.36981;187.53476;-47.06566;,
 84.36981;191.65368;-47.06566;,
 84.36981;191.65368;54.84054;,
 84.36981;187.53476;54.84054;,
 84.36981;191.65368;54.84054;,
 84.36981;191.65368;-47.06566;,
 -55.48333;71.41953;-47.06567;,
 -55.48333;71.41953;54.84054;,
 84.36981;187.53476;-47.06566;,
 84.36981;187.53476;54.84054;,
 -46.72452;70.95510;54.84054;,
 -46.72452;70.95510;-47.06567;,
 84.96889;-1.43314;-48.28471;,
 78.87457;-1.43314;-48.28471;,
 78.87457;65.39579;-48.28471;,
 84.96889;65.39579;-48.28471;,
 78.87457;65.39579;-37.03556;,
 84.96889;65.39579;-37.03556;,
 78.87457;-1.43314;-37.03556;,
 84.96889;-1.43314;-37.03556;,
 78.87457;-1.43314;-48.28471;,
 84.96889;-1.43314;-48.28471;,
 78.87457;-1.43314;-37.03556;,
 78.87457;65.39579;-37.03556;,
 84.96889;-1.43314;-37.03556;,
 84.96889;65.39579;-37.03556;,
 85.19163;65.23419;-48.39744;,
 15.98745;65.23419;-48.39744;,
 15.98745;70.10576;-48.39743;,
 85.19163;70.10576;-48.39743;,
 15.98745;81.93317;-37.17136;,
 85.19163;81.93317;-37.17136;,
 15.98745;65.23419;-37.17135;,
 85.19163;65.23419;-37.17135;,
 15.98745;65.23419;-48.39744;,
 85.19163;65.23419;-48.39744;,
 15.98745;65.23419;-37.17135;,
 15.98745;81.93317;-37.17136;,
 85.19163;65.23419;-37.17135;,
 85.19163;81.93317;-37.17136;,
 23.83768;-1.07255;-45.49237;,
 16.70656;-1.07255;-45.49237;,
 16.70656;67.42171;-45.49237;,
 23.83768;67.42171;-45.49237;,
 16.70656;67.42171;-41.78239;,
 23.83768;67.42171;-41.78239;,
 16.70656;-1.07255;-41.78239;,
 23.83768;-1.07255;-41.78239;,
 16.70656;-1.07255;-45.49237;,
 23.83768;-1.07255;-45.49237;,
 16.70656;-1.07255;-41.78239;,
 16.70656;67.42171;-41.78239;,
 23.83768;-1.07255;-41.78239;,
 23.83768;67.42171;-41.78239;,
 51.30264;0.74922;-37.49400;,
 25.80417;0.74922;-37.49400;,
 25.80417;48.04039;-37.49401;,
 51.30264;48.04039;-37.49401;,
 54.47946;32.10754;-37.67776;,
 54.55721;44.84826;-37.67776;,
 73.02416;44.81557;-37.67776;,
 72.94642;32.07483;-37.67776;,
 54.47946;19.75523;-37.67776;,
 54.55721;32.49595;-37.67776;,
 73.02416;32.46326;-37.67776;,
 72.94642;19.72252;-37.67776;,
 108.85958;112.48688;-37.37134;,
 59.30487;112.48688;-37.37134;,
 59.30487;145.71372;-37.37132;,
 108.85958;145.71372;-37.37132;,
 143.29737;36.25353;-37.37134;,
 108.31980;36.25353;-37.37134;,
 108.31980;59.70627;-37.37132;,
 143.29737;59.70627;-37.37132;,
 15.20741;42.85123;-29.47903;,
 15.20741;42.85123;-11.28202;,
 15.20743;58.56539;-11.28202;,
 15.20743;58.56539;-29.47903;,
 15.20741;26.61593;13.43033;,
 15.20741;26.61593;31.62734;,
 15.20743;55.58204;31.62734;,
 15.20743;55.58204;13.43033;,
 -54.50717;-0.32008;-32.99888;,
 -56.51864;-0.32008;-32.99888;,
 -56.51864;43.55058;-32.99888;,
 -54.50717;43.55058;-32.99888;,
 -54.50717;43.55058;-32.99888;,
 -56.51864;43.55058;-32.99888;,
 -56.51864;43.55058;-30.98741;,
 -54.50717;43.55058;-30.98741;,
 -54.50717;43.55058;-30.98741;,
 -56.51864;43.55058;-30.98741;,
 -56.51864;-0.32008;-30.98741;,
 -54.50717;-0.32008;-30.98741;,
 -54.50717;-0.32008;-30.98741;,
 -56.51864;-0.32008;-30.98741;,
 -56.51864;-0.32008;-32.99888;,
 -54.50717;-0.32008;-32.99888;,
 -56.51864;-0.32008;-32.99888;,
 -56.51864;-0.32008;-30.98741;,
 -56.51864;43.55058;-30.98741;,
 -56.51864;43.55058;-32.99888;,
 -54.50717;-0.32008;-30.98741;,
 -54.50717;-0.32008;-32.99888;,
 -54.50717;43.55058;-32.99888;,
 -54.50717;43.55058;-30.98741;,
 -54.50717;-0.32008;-43.64353;,
 -56.51864;-0.32008;-43.64353;,
 -56.51864;43.55058;-43.64353;,
 -54.50717;43.55058;-43.64353;,
 -54.50717;43.55058;-43.64353;,
 -56.51864;43.55058;-43.64353;,
 -56.51864;43.55058;-41.63206;,
 -54.50717;43.55058;-41.63206;,
 -54.50717;43.55058;-41.63206;,
 -56.51864;43.55058;-41.63206;,
 -56.51864;-0.32008;-41.63206;,
 -54.50717;-0.32008;-41.63206;,
 -54.50717;-0.32008;-41.63206;,
 -56.51864;-0.32008;-41.63206;,
 -56.51864;-0.32008;-43.64353;,
 -54.50717;-0.32008;-43.64353;,
 -56.51864;-0.32008;-43.64353;,
 -56.51864;-0.32008;-41.63206;,
 -56.51864;43.55058;-41.63206;,
 -56.51864;43.55058;-43.64353;,
 -54.50717;-0.32008;-41.63206;,
 -54.50717;-0.32008;-43.64353;,
 -54.50717;43.55058;-43.64353;,
 -54.50717;43.55058;-41.63206;,
 -54.50717;-0.32008;-21.64309;,
 -56.51864;-0.32008;-21.64309;,
 -56.51864;43.55058;-21.64309;,
 -54.50717;43.55058;-21.64309;,
 -54.50717;43.55058;-21.64309;,
 -56.51864;43.55058;-21.64309;,
 -56.51864;43.55058;-19.63161;,
 -54.50717;43.55058;-19.63161;,
 -54.50717;43.55058;-19.63161;,
 -56.51864;43.55058;-19.63161;,
 -56.51864;-0.32008;-19.63161;,
 -54.50717;-0.32008;-19.63161;,
 -54.50717;-0.32008;-19.63161;,
 -56.51864;-0.32008;-19.63161;,
 -56.51864;-0.32008;-21.64309;,
 -54.50717;-0.32008;-21.64309;,
 -56.51864;-0.32008;-21.64309;,
 -56.51864;-0.32008;-19.63161;,
 -56.51864;43.55058;-19.63161;,
 -56.51864;43.55058;-21.64309;,
 -54.50717;-0.32008;-19.63161;,
 -54.50717;-0.32008;-21.64309;,
 -54.50717;43.55058;-21.64309;,
 -54.50717;43.55058;-19.63161;,
 -54.50717;-0.32008;-9.26404;,
 -56.51864;-0.32008;-9.26404;,
 -56.51864;43.55058;-9.26404;,
 -54.50717;43.55058;-9.26404;,
 -54.50717;43.55058;-9.26404;,
 -56.51864;43.55058;-9.26404;,
 -56.51864;43.55058;-7.25257;,
 -54.50717;43.55058;-7.25257;,
 -54.50717;43.55058;-7.25257;,
 -56.51864;43.55058;-7.25257;,
 -56.51864;-0.32008;-7.25257;,
 -54.50717;-0.32008;-7.25257;,
 -54.50717;-0.32008;-7.25257;,
 -56.51864;-0.32008;-7.25257;,
 -56.51864;-0.32008;-9.26404;,
 -54.50717;-0.32008;-9.26404;,
 -56.51864;-0.32008;-9.26404;,
 -56.51864;-0.32008;-7.25257;,
 -56.51864;43.55058;-7.25257;,
 -56.51864;43.55058;-9.26404;,
 -54.50717;-0.32008;-7.25257;,
 -54.50717;-0.32008;-9.26404;,
 -54.50717;43.55058;-9.26404;,
 -54.50717;43.55058;-7.25257;,
 -54.50717;-0.32008;1.38061;,
 -56.51864;-0.32008;1.38061;,
 -56.51864;43.55058;1.38061;,
 -54.50717;43.55058;1.38061;,
 -54.50717;43.55058;1.38061;,
 -56.51864;43.55058;1.38061;,
 -56.51864;43.55058;3.39208;,
 -54.50717;43.55058;3.39208;,
 -54.50717;43.55058;3.39208;,
 -56.51864;43.55058;3.39208;,
 -56.51864;-0.32008;3.39208;,
 -54.50717;-0.32008;3.39208;,
 -54.50717;-0.32008;3.39208;,
 -56.51864;-0.32008;3.39208;,
 -56.51864;-0.32008;1.38061;,
 -54.50717;-0.32008;1.38061;,
 -56.51864;-0.32008;1.38061;,
 -56.51864;-0.32008;3.39208;,
 -56.51864;43.55058;3.39208;,
 -56.51864;43.55058;1.38061;,
 -54.50717;-0.32008;3.39208;,
 -54.50717;-0.32008;1.38061;,
 -54.50717;43.55058;1.38061;,
 -54.50717;43.55058;3.39208;,
 -54.50717;-0.32008;12.73640;,
 -56.51864;-0.32008;12.73640;,
 -56.51864;43.55058;12.73640;,
 -54.50717;43.55058;12.73640;,
 -54.50717;43.55058;12.73640;,
 -56.51864;43.55058;12.73640;,
 -56.51864;43.55058;14.74787;,
 -54.50717;43.55058;14.74787;,
 -54.50717;43.55058;14.74787;,
 -56.51864;43.55058;14.74787;,
 -56.51864;-0.32008;14.74787;,
 -54.50717;-0.32008;14.74787;,
 -54.50717;-0.32008;14.74787;,
 -56.51864;-0.32008;14.74787;,
 -56.51864;-0.32008;12.73640;,
 -54.50717;-0.32008;12.73640;,
 -56.51864;-0.32008;12.73640;,
 -56.51864;-0.32008;14.74787;,
 -56.51864;43.55058;14.74787;,
 -56.51864;43.55058;12.73640;,
 -54.50717;-0.32008;14.74787;,
 -54.50717;-0.32008;12.73640;,
 -54.50717;43.55058;12.73640;,
 -54.50717;43.55058;14.74787;,
 -54.50717;-0.32008;22.00788;,
 -56.51864;-0.32008;22.00788;,
 -56.51864;43.55058;22.00788;,
 -54.50717;43.55058;22.00788;,
 -54.50717;43.55058;22.00788;,
 -56.51864;43.55058;22.00788;,
 -56.51864;43.55058;24.01935;,
 -54.50717;43.55058;24.01935;,
 -54.50717;43.55058;24.01935;,
 -56.51864;43.55058;24.01935;,
 -56.51864;-0.32008;24.01935;,
 -54.50717;-0.32008;24.01935;,
 -54.50717;-0.32008;24.01935;,
 -56.51864;-0.32008;24.01935;,
 -56.51864;-0.32008;22.00788;,
 -54.50717;-0.32008;22.00788;,
 -56.51864;-0.32008;22.00788;,
 -56.51864;-0.32008;24.01935;,
 -56.51864;43.55058;24.01935;,
 -56.51864;43.55058;22.00788;,
 -54.50717;-0.32008;24.01935;,
 -54.50717;-0.32008;22.00788;,
 -54.50717;43.55058;22.00788;,
 -54.50717;43.55058;24.01935;,
 -54.50717;-0.32008;32.65254;,
 -56.51864;-0.32008;32.65254;,
 -56.51864;43.55058;32.65254;,
 -54.50717;43.55058;32.65254;,
 -54.50717;43.55058;32.65254;,
 -56.51864;43.55058;32.65254;,
 -56.51864;43.55058;34.66401;,
 -54.50717;43.55058;34.66401;,
 -54.50717;43.55058;34.66401;,
 -56.51864;43.55058;34.66401;,
 -56.51864;-0.32008;34.66401;,
 -54.50717;-0.32008;34.66401;,
 -54.50717;-0.32008;34.66401;,
 -56.51864;-0.32008;34.66401;,
 -56.51864;-0.32008;32.65254;,
 -54.50717;-0.32008;32.65254;,
 -56.51864;-0.32008;32.65254;,
 -56.51864;-0.32008;34.66401;,
 -56.51864;43.55058;34.66401;,
 -56.51864;43.55058;32.65254;,
 -54.50717;-0.32008;34.66401;,
 -54.50717;-0.32008;32.65254;,
 -54.50717;43.55058;32.65254;,
 -54.50717;43.55058;34.66401;,
 -54.50717;-0.32008;42.90748;,
 -56.51864;-0.32008;42.90748;,
 -56.51864;43.55058;42.90748;,
 -54.50717;43.55058;42.90748;,
 -54.50717;43.55058;42.90748;,
 -56.51864;43.55058;42.90748;,
 -56.51864;43.55058;44.91895;,
 -54.50717;43.55058;44.91895;,
 -54.50717;43.55058;44.91895;,
 -56.51864;43.55058;44.91895;,
 -56.51864;-0.32008;44.91895;,
 -54.50717;-0.32008;44.91895;,
 -54.50717;-0.32008;44.91895;,
 -56.51864;-0.32008;44.91895;,
 -56.51864;-0.32008;42.90748;,
 -54.50717;-0.32008;42.90748;,
 -56.51864;-0.32008;42.90748;,
 -56.51864;-0.32008;44.91895;,
 -56.51864;43.55058;44.91895;,
 -56.51864;43.55058;42.90748;,
 -54.50717;-0.32008;44.91895;,
 -54.50717;-0.32008;42.90748;,
 -54.50717;43.55058;42.90748;,
 -54.50717;43.55058;44.91895;,
 15.19936;0.26249;-39.33492;,
 -53.41734;0.26249;-39.33492;,
 -53.41734;1.96906;-39.33492;,
 15.19936;1.96906;-39.33492;,
 15.19936;1.96906;-39.33492;,
 -53.41734;1.96906;-39.33492;,
 -53.41734;1.96906;45.96113;,
 15.19936;1.96906;45.96113;,
 15.19936;1.96906;45.96113;,
 -53.41734;1.96906;45.96113;,
 -53.41734;0.26249;45.96113;,
 15.19936;0.26249;45.96113;,
 15.19936;0.26249;45.96113;,
 -53.41734;0.26249;45.96113;,
 -53.41734;0.26249;-39.33492;,
 15.19936;0.26249;-39.33492;,
 -53.41734;0.26249;-39.33492;,
 -53.41734;0.26249;45.96113;,
 -53.41734;1.96906;45.96113;,
 -53.41734;1.96906;-39.33492;,
 15.19936;0.26249;45.96113;,
 15.19936;0.26249;-39.33492;,
 15.19936;1.96906;-39.33492;,
 15.19936;1.96906;45.96113;;
 
 151;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 3;72,73,74;,
 3;75,76,77;,
 4;78,79,80,81;,
 4;73,82,83,74;,
 4;84,72,74,85;,
 4;86,87,73,72;,
 4;87,88,82,73;,
 4;77,76,79,78;,
 4;89,86,72,84;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;114,115,116,117;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,135,136,137;,
 4;138,139,140,141;,
 4;141,140,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 4;139,148,149,140;,
 4;150,138,141,151;,
 4;152,153,154,155;,
 4;155,154,156,157;,
 4;157,156,158,159;,
 4;159,158,160,161;,
 4;153,162,163,154;,
 4;164,152,155,165;,
 4;166,167,168,169;,
 4;169,168,170,171;,
 4;171,170,172,173;,
 4;173,172,174,175;,
 4;167,176,177,168;,
 4;178,166,169,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;192,193,194,195;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 3;72,73,74;,
 3;75,76,77;,
 4;78,79,80,81;,
 4;73,82,83,74;,
 4;84,72,74,85;,
 4;86,87,73,72;,
 4;87,88,82,73;,
 4;77,76,79,78;,
 4;89,86,72,84;,
 4;208,209,210,211;,
 4;212,213,214,215;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;228,229,230,231;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;268,269,270,271;,
 4;272,273,274,275;,
 4;276,277,278,279;,
 4;280,281,282,283;,
 4;284,285,286,287;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;300,301,302,303;,
 4;304,305,306,307;,
 4;308,309,310,311;,
 4;312,313,314,315;,
 4;316,317,318,319;,
 4;320,321,322,323;,
 4;324,325,326,327;,
 4;328,329,330,331;,
 4;332,333,334,335;,
 4;336,337,338,339;,
 4;340,341,342,343;,
 4;344,345,346,347;,
 4;348,349,350,351;,
 4;352,353,354,355;,
 4;356,357,358,359;,
 4;360,361,362,363;,
 4;364,365,366,367;,
 4;368,369,370,371;,
 4;372,373,374,375;,
 4;376,377,378,379;,
 4;380,381,382,383;,
 4;384,385,386,387;,
 4;388,389,390,391;,
 4;392,393,394,395;,
 4;396,397,398,399;,
 4;400,401,402,403;,
 4;404,405,406,407;,
 4;408,409,410,411;,
 4;412,413,414,415;,
 4;416,417,418,419;,
 4;420,421,422,423;,
 4;424,425,426,427;,
 4;428,429,430,431;,
 4;432,433,434,435;,
 4;436,437,438,439;,
 4;440,441,442,443;,
 4;444,445,446,447;,
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;;
 
 MeshMaterialList {
  1;
  151;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\House.jpg";
   }
  }
 }
 MeshNormals {
  34;
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.908822;0.417183;0.000000;,
  -0.946367;-0.323094;0.000000;,
  0.330604;-0.943770;-0.000000;,
  -0.052950;-0.998597;0.000000;,
  0.000000;0.000002;-1.000000;,
  0.000000;0.370605;-0.928790;,
  0.000000;0.688428;-0.725305;,
  0.000000;0.000001;1.000000;,
  0.000000;-0.000000;-1.000000;,
  0.000000;0.000001;-1.000000;,
  0.000000;0.000001;-1.000000;,
  -1.000000;0.000001;0.000000;,
  -1.000000;0.000001;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.949032;0.315181;-0.000000;,
  -0.801322;0.598233;-0.000000;,
  0.949031;0.315182;-0.000000;,
  0.801322;0.598233;-0.000000;,
  -1.000000;-0.000001;0.000000;,
  1.000000;0.000001;-0.000000;,
  0.469596;-0.882881;-0.000000;,
  -0.791221;-0.611530;0.000000;,
  0.766348;0.642425;0.000000;,
  0.939773;0.341798;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.912285;-0.409556;-0.000000;,
  -0.651916;0.758291;0.000000;;
  151;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  3;1,1,1;,
  3;3,3,3;,
  4;0,0,0,0;,
  4;21,21,22,22;,
  4;23,23,24,24;,
  4;1,1,1,1;,
  4;25,25,21,21;,
  4;3,3,3,3;,
  4;26,26,23,23;,
  4;4,4,5,5;,
  4;6,7,7,6;,
  4;3,3,3,3;,
  4;27,27,27,27;,
  4;28,28,7,7;,
  4;29,29,30,30;,
  4;3,3,3,3;,
  4;8,9,9,8;,
  4;31,31,5,5;,
  4;32,30,30,32;,
  4;6,6,33,33;,
  4;32,32,8,8;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;13,13,13,13;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;14,14,14,14;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  3;1,1,1;,
  3;3,3,3;,
  4;0,0,0,0;,
  4;21,21,22,22;,
  4;23,23,24,24;,
  4;1,1,1,1;,
  4;25,25,21,21;,
  4;3,3,3,3;,
  4;26,26,23,23;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;19,19,19,19;,
  4;20,20,20,20;;
 }
 MeshTextureCoords {
  448;
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.236792;0.496736;,
  0.279747;0.496736;,
  0.258270;0.475395;,
  0.258270;0.432440;,
  0.279747;0.411099;,
  0.236792;0.411099;,
  0.236792;0.389485;,
  0.279747;0.389485;,
  0.279747;0.346530;,
  0.236792;0.346530;,
  0.322702;0.496736;,
  0.322702;0.475395;,
  0.193837;0.496736;,
  0.193837;0.475395;,
  0.236792;0.518350;,
  0.279747;0.518350;,
  0.322702;0.518350;,
  0.193837;0.518350;,
  0.626623;0.372766;,
  0.876623;0.372766;,
  0.876623;0.122766;,
  0.626623;0.122766;,
  0.689739;0.350812;,
  0.939739;0.350812;,
  0.939739;0.100812;,
  0.689739;0.100812;,
  0.626623;0.372365;,
  0.876623;0.372365;,
  0.876623;0.122365;,
  0.626623;0.122365;,
  0.689739;0.375378;,
  0.939739;0.375378;,
  0.939739;0.125378;,
  0.689739;0.125378;,
  0.690641;0.361011;,
  0.940641;0.361011;,
  0.940641;0.111011;,
  0.690641;0.111011;,
  0.624599;0.387352;,
  0.874599;0.387352;,
  0.874599;0.137352;,
  0.624599;0.137352;,
  0.626623;0.372766;,
  0.876623;0.372766;,
  0.876623;0.122766;,
  0.626623;0.122766;,
  0.689739;0.350812;,
  0.939739;0.350812;,
  0.939739;0.100812;,
  0.689739;0.100812;,
  0.626623;0.372365;,
  0.876623;0.372365;,
  0.876623;0.122365;,
  0.626623;0.122365;,
  0.689739;0.375378;,
  0.939739;0.375378;,
  0.939739;0.125378;,
  0.689739;0.125378;,
  0.625000;0.387352;,
  0.875000;0.387352;,
  0.875000;0.137352;,
  0.625000;0.137352;,
  0.682947;0.361011;,
  0.932947;0.361011;,
  0.932947;0.111011;,
  0.682947;0.111011;,
  0.216955;0.550177;,
  0.263611;0.550177;,
  0.263611;0.503521;,
  0.216955;0.503521;,
  0.263611;0.456866;,
  0.216955;0.456866;,
  0.263611;0.410210;,
  0.216955;0.410210;,
  0.263611;0.363554;,
  0.216955;0.363554;,
  0.310267;0.550177;,
  0.310267;0.503521;,
  0.170300;0.550177;,
  0.170300;0.503521;,
  0.700775;0.501033;,
  0.789637;0.501033;,
  0.789637;0.412170;,
  0.700775;0.412170;,
  0.789637;0.323307;,
  0.700775;0.323307;,
  0.789637;0.234445;,
  0.700775;0.234445;,
  0.789637;0.145582;,
  0.700775;0.145582;,
  0.878500;0.501033;,
  0.878500;0.412170;,
  0.611912;0.501033;,
  0.611912;0.412170;,
  0.741368;0.425203;,
  0.792316;0.425203;,
  0.792316;0.374255;,
  0.741368;0.374255;,
  0.792316;0.323307;,
  0.741368;0.323307;,
  0.792316;0.272360;,
  0.741368;0.272360;,
  0.792316;0.221412;,
  0.741368;0.221412;,
  0.843264;0.425203;,
  0.843264;0.374255;,
  0.690420;0.425203;,
  0.690420;0.374255;,
  0.744892;1.003589;,
  0.999732;1.000721;,
  0.999732;0.592385;,
  0.742024;0.589517;,
  0.250211;0.999825;,
  0.495697;0.997529;,
  0.495697;0.633141;,
  0.248467;0.630845;,
  0.250211;0.999825;,
  0.495697;0.997529;,
  0.495697;0.633141;,
  0.248467;0.630845;,
  0.000035;0.997708;,
  0.499161;0.998916;,
  0.499161;0.635939;,
  0.000321;0.631380;,
  0.000035;0.997708;,
  0.499161;0.998916;,
  0.499161;0.635939;,
  0.000321;0.631380;,
  0.000035;0.997708;,
  0.499161;0.998916;,
  0.499161;0.635939;,
  0.000321;0.631380;,
  0.000035;0.997708;,
  0.499161;0.998916;,
  0.499161;0.635939;,
  0.000321;0.631380;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  0.499218;0.888817;,
  0.508069;0.888817;,
  0.508069;0.637854;,
  0.499218;0.637854;,
  0.499218;0.889281;,
  0.508069;0.889281;,
  0.508069;0.640245;,
  0.499218;0.640245;,
  0.499218;0.889065;,
  0.508069;0.889065;,
  0.508069;0.639128;,
  0.499218;0.639128;,
  0.499218;0.889188;,
  0.508069;0.889188;,
  0.508069;0.639765;,
  0.499218;0.639765;,
  0.499186;0.888817;,
  0.508056;0.888817;,
  0.508056;0.637854;,
  0.499186;0.637854;,
  0.499223;0.888817;,
  0.508071;0.888817;,
  0.508071;0.637854;,
  0.499223;0.637854;,
  -0.001743;0.293208;,
  0.490872;0.295165;,
  0.492829;0.007990;,
  0.004126;0.000164;,
  -0.001743;0.293048;,
  0.490872;0.295005;,
  0.492829;0.007830;,
  0.004126;0.000004;,
  -0.001743;0.290313;,
  0.490872;0.292269;,
  0.492829;0.005094;,
  0.004126;-0.002732;,
  -0.001743;0.290153;,
  0.490872;0.292109;,
  0.492829;0.004934;,
  0.004126;-0.002892;,
  -0.001583;0.293208;,
  0.491032;0.295165;,
  0.492989;0.007990;,
  0.004286;0.000164;,
  -0.001903;0.293208;,
  0.490712;0.295165;,
  0.492669;0.007990;,
  0.003966;0.000164;;
 }
}
