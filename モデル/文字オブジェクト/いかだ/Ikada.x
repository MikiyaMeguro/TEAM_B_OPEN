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
 186;
 29.79062;0.60525;-0.04510;,
 -29.79062;0.60525;-0.04510;,
 -29.79062;-1.89475;-1.90141;,
 29.79062;-1.89475;-1.90141;,
 -29.79062;-2.84967;-4.92454;,
 29.79062;-2.84967;-4.92454;,
 -29.79062;-1.89475;-7.94766;,
 29.79062;-1.89475;-7.94766;,
 -29.79062;0.60525;-9.81242;,
 29.79062;0.60525;-9.81242;,
 -29.79062;3.69542;-9.81242;,
 29.79062;3.69542;-9.81242;,
 -29.79062;6.19542;-7.94766;,
 29.79062;6.19542;-7.94766;,
 -29.79062;7.15034;-4.92454;,
 29.79062;7.15034;-4.92454;,
 -29.79062;6.19542;-1.90141;,
 29.79062;6.19542;-1.90141;,
 -29.79062;3.69542;-0.04510;,
 29.79062;3.69542;-0.04510;,
 -29.79062;0.60525;-0.04510;,
 29.79062;0.60525;-0.04510;,
 -29.79062;0.60525;-0.04510;,
 -29.79062;3.69542;-0.04510;,
 -29.79062;-1.89475;-1.90141;,
 -29.79062;6.19542;-1.90141;,
 -29.79062;7.15034;-4.92454;,
 -29.79062;-2.84967;-4.92454;,
 -29.79062;6.19542;-7.94766;,
 -29.79062;-1.89475;-7.94766;,
 -29.79062;3.69542;-9.81242;,
 -29.79062;0.60525;-9.81242;,
 29.79062;3.69542;-9.81242;,
 29.79062;6.19542;-7.94766;,
 29.79062;0.60525;-9.81242;,
 29.79062;-1.89475;-7.94766;,
 29.79062;7.15034;-4.92454;,
 29.79062;-2.84967;-4.92454;,
 29.79062;6.19542;-1.90141;,
 29.79062;-1.89475;-1.90141;,
 29.79062;3.69542;-0.04510;,
 29.79062;0.60525;-0.04510;,
 29.79062;0.60525;9.72023;,
 -29.79062;0.60525;9.72023;,
 -29.79062;-1.89475;7.85748;,
 29.79062;-1.89475;7.85748;,
 -29.79062;-2.84967;4.83434;,
 29.79062;-2.84967;4.83434;,
 -29.79062;-1.89475;1.81122;,
 29.79062;-1.89475;1.81122;,
 -29.79062;0.60525;-0.04510;,
 29.79062;0.60525;-0.04510;,
 -29.79062;3.69542;-0.04510;,
 29.79062;3.69542;-0.04510;,
 -29.79062;6.19542;1.81122;,
 29.79062;6.19542;1.81122;,
 -29.79062;7.15034;4.83434;,
 29.79062;7.15034;4.83434;,
 -29.79062;6.19542;7.85747;,
 29.79062;6.19542;7.85747;,
 -29.79062;3.69542;9.72023;,
 29.79062;3.69542;9.72023;,
 -29.79062;0.60525;9.72023;,
 29.79062;0.60525;9.72023;,
 -29.79062;0.60525;9.72023;,
 -29.79062;3.69542;9.72023;,
 -29.79062;-1.89475;7.85748;,
 -29.79062;6.19542;7.85747;,
 -29.79062;-2.84967;4.83434;,
 -29.79062;7.15034;4.83434;,
 -29.79062;6.19542;1.81122;,
 -29.79062;-1.89475;1.81122;,
 -29.79062;3.69542;-0.04510;,
 -29.79062;0.60525;-0.04510;,
 29.79062;3.69542;-0.04510;,
 29.79062;6.19542;1.81122;,
 29.79062;0.60525;-0.04510;,
 29.79062;-1.89475;1.81122;,
 29.79062;7.15034;4.83434;,
 29.79062;-2.84967;4.83434;,
 29.79062;6.19542;7.85747;,
 29.79062;-1.89475;7.85748;,
 29.79062;3.69542;9.72023;,
 29.79062;0.60525;9.72023;,
 29.79062;0.60525;-9.81242;,
 -29.79062;0.60525;-9.81242;,
 -29.79062;-1.89475;-11.67717;,
 29.79062;-1.89475;-11.67717;,
 -29.79062;-2.84967;-14.70031;,
 29.79062;-2.84967;-14.70031;,
 -29.79062;-1.89475;-17.72343;,
 29.79062;-1.89475;-17.72343;,
 -29.79062;0.60525;-19.59183;,
 29.79062;0.60525;-19.59183;,
 -29.79062;3.69542;-19.59183;,
 29.79062;3.69542;-19.59183;,
 -29.79062;6.19542;-17.72343;,
 29.79062;6.19542;-17.72343;,
 -29.79062;7.15034;-14.70031;,
 29.79062;7.15034;-14.70031;,
 -29.79062;6.19542;-11.67718;,
 29.79062;6.19542;-11.67718;,
 -29.79062;3.69542;-9.81242;,
 29.79062;3.69542;-9.81242;,
 -29.79062;0.60525;-9.81242;,
 29.79062;0.60525;-9.81242;,
 -29.79062;0.60525;-9.81242;,
 -29.79062;3.69542;-9.81242;,
 -29.79062;-1.89475;-11.67717;,
 -29.79062;6.19542;-11.67718;,
 -29.79062;-2.84967;-14.70031;,
 -29.79062;7.15034;-14.70031;,
 -29.79062;6.19542;-17.72343;,
 -29.79062;-1.89475;-17.72343;,
 -29.79062;3.69542;-19.59183;,
 -29.79062;0.60525;-19.59183;,
 29.79062;0.60525;-19.59183;,
 29.79062;3.69542;-19.59183;,
 29.79062;-1.89475;-17.72343;,
 29.79062;6.19542;-17.72343;,
 29.79062;7.15034;-14.70031;,
 29.79062;-2.84967;-14.70031;,
 29.79062;6.19542;-11.67718;,
 29.79062;-1.89475;-11.67717;,
 29.79062;3.69542;-9.81242;,
 29.79062;0.60525;-9.81242;,
 29.79062;0.60525;19.49765;,
 -29.79062;0.60525;19.49765;,
 -29.79062;-1.89475;17.62925;,
 29.79062;-1.89475;17.62925;,
 -29.79062;-2.84967;14.60613;,
 29.79062;-2.84967;14.60613;,
 -29.79062;-1.89475;11.58299;,
 29.79062;-1.89475;11.58299;,
 -29.79062;0.60525;9.72023;,
 29.79062;0.60525;9.72023;,
 -29.79062;3.69542;9.72023;,
 29.79062;3.69542;9.72023;,
 -29.79062;6.19542;11.58299;,
 29.79062;6.19542;11.58299;,
 -29.79062;7.15034;14.60613;,
 29.79062;7.15034;14.60613;,
 -29.79062;6.19542;17.62925;,
 29.79062;6.19542;17.62925;,
 -29.79062;3.69542;19.49765;,
 29.79062;3.69542;19.49765;,
 -29.79062;0.60525;19.49765;,
 29.79062;0.60525;19.49765;,
 -29.79062;0.60525;19.49765;,
 -29.79062;3.69542;19.49765;,
 -29.79062;-1.89475;17.62925;,
 -29.79062;6.19542;17.62925;,
 -29.79062;7.15034;14.60613;,
 -29.79062;-2.84967;14.60613;,
 -29.79062;6.19542;11.58299;,
 -29.79062;-1.89475;11.58299;,
 -29.79062;3.69542;9.72023;,
 -29.79062;0.60525;9.72023;,
 29.79062;3.69542;9.72023;,
 29.79062;6.19542;11.58299;,
 29.79062;0.60525;9.72023;,
 29.79062;-1.89475;11.58299;,
 29.79062;7.15034;14.60613;,
 29.79062;-2.84967;14.60613;,
 29.79062;6.19542;17.62925;,
 29.79062;-1.89475;17.62925;,
 29.79062;3.69542;19.49765;,
 29.79062;0.60525;19.49765;,
 -28.33438;1.86789;-0.05914;,
 -26.54916;1.86789;1.84435;,
 -26.54916;65.30140;1.84435;,
 -28.33438;65.30140;-0.05914;,
 -26.54916;65.30140;1.84435;,
 -26.43089;65.30140;-1.84435;,
 -28.33438;65.30140;-0.05914;,
 -26.43089;1.86789;-1.84435;,
 -26.43089;65.30140;-1.84435;,
 -26.54916;1.86789;1.84435;,
 -26.43089;1.86789;-1.84435;,
 -26.43089;65.30140;-1.84435;,
 -26.54916;1.86789;1.84435;,
 -28.33438;1.86789;-0.05914;,
 -26.43089;1.86789;-1.84435;,
 -26.91242;42.68627;0.00000;,
 -26.91242;64.64301;0.00000;,
 1.25202;53.66464;0.00000;;
 
 111;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 3;22,23,24;,
 3;23,25,24;,
 3;25,26,24;,
 3;24,26,27;,
 3;26,28,27;,
 3;27,28,29;,
 3;28,30,29;,
 3;30,31,29;,
 3;32,33,34;,
 3;34,33,35;,
 3;33,36,35;,
 3;35,36,37;,
 3;36,38,37;,
 3;37,38,39;,
 3;38,40,39;,
 3;40,41,39;,
 4;42,43,44,45;,
 4;45,44,46,47;,
 4;47,46,48,49;,
 4;49,48,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;55,54,56,57;,
 4;57,56,58,59;,
 4;59,58,60,61;,
 4;61,60,62,63;,
 3;64,65,66;,
 3;65,67,66;,
 3;66,67,68;,
 3;67,69,68;,
 3;69,70,68;,
 3;68,70,71;,
 3;70,72,71;,
 3;72,73,71;,
 3;74,75,76;,
 3;76,75,77;,
 3;75,78,77;,
 3;77,78,79;,
 3;78,80,79;,
 3;79,80,81;,
 3;80,82,81;,
 3;82,83,81;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;89,88,90,91;,
 4;91,90,92,93;,
 4;93,92,94,95;,
 4;95,94,96,97;,
 4;97,96,98,99;,
 4;99,98,100,101;,
 4;101,100,102,103;,
 4;103,102,104,105;,
 3;106,107,108;,
 3;107,109,108;,
 3;108,109,110;,
 3;109,111,110;,
 3;111,112,110;,
 3;110,112,113;,
 3;112,114,113;,
 3;114,115,113;,
 3;116,117,118;,
 3;117,119,118;,
 3;119,120,118;,
 3;118,120,121;,
 3;120,122,121;,
 3;121,122,123;,
 3;122,124,123;,
 3;124,125,123;,
 4;126,127,128,129;,
 4;129,128,130,131;,
 4;131,130,132,133;,
 4;133,132,134,135;,
 4;135,134,136,137;,
 4;137,136,138,139;,
 4;139,138,140,141;,
 4;141,140,142,143;,
 4;143,142,144,145;,
 4;145,144,146,147;,
 3;148,149,150;,
 3;149,151,150;,
 3;151,152,150;,
 3;150,152,153;,
 3;152,154,153;,
 3;153,154,155;,
 3;154,156,155;,
 3;156,157,155;,
 3;158,159,160;,
 3;160,159,161;,
 3;159,162,161;,
 3;161,162,163;,
 3;162,164,163;,
 3;163,164,165;,
 3;164,166,165;,
 3;166,167,165;,
 4;168,169,170,171;,
 3;172,173,174;,
 4;175,168,171,176;,
 4;177,178,179,170;,
 3;180,181,182;,
 3;183,184,185;,
 3;185,184,183;;
 
 MeshMaterialList {
  1;
  111;
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
    "C:\\Users\\game105\\Desktop\\MODEL\\UV\\Ikada.jpg";
   }
  }
 }
 MeshNormals {
  48;
  0.000000;-0.313949;0.949440;,
  0.000000;-0.814445;0.580240;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.815075;-0.579355;,
  0.000000;-0.314982;-0.949098;,
  0.000000;0.314981;-0.949098;,
  0.000000;0.815075;-0.579355;,
  0.000000;1.000000;-0.000000;,
  0.000000;0.814445;0.580241;,
  0.000000;0.313950;0.949439;,
  0.000000;-0.314737;0.949179;,
  0.000000;-0.814927;0.579564;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.814445;-0.580241;,
  0.000000;0.814445;-0.580240;,
  0.000000;1.000000;0.000000;,
  0.000000;0.814926;0.579564;,
  0.000000;0.314738;0.949179;,
  0.000000;-0.815075;0.579355;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.815346;-0.578974;,
  0.000000;-0.315425;-0.948951;,
  0.000000;0.315425;-0.948951;,
  0.000000;0.815346;-0.578974;,
  0.000000;0.815075;0.579355;,
  0.000000;-0.315425;0.948951;,
  0.000000;-0.815346;0.578974;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.814927;-0.579564;,
  0.000000;0.814927;-0.579564;,
  0.000000;1.000000;0.000000;,
  0.000000;0.815346;0.578974;,
  0.000000;0.315425;0.948950;,
  -0.729403;0.000000;0.684085;,
  0.000000;1.000000;0.000000;,
  -0.684083;0.000000;-0.729404;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;-0.313950;-0.949439;,
  0.000000;0.313949;-0.949440;,
  0.000000;-0.314980;0.949098;,
  0.000000;0.314982;0.949098;,
  0.000000;-0.314738;-0.949178;,
  0.000000;0.314737;-0.949179;,
  0.999486;0.000000;0.032045;,
  0.000000;-1.000000;0.000000;,
  0.000000;0.000000;1.000000;;
  111;
  4;0,0,1,1;,
  4;1,1,2,2;,
  4;2,2,3,3;,
  4;3,3,4,4;,
  4;4,4,5,5;,
  4;5,5,6,6;,
  4;6,6,7,7;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,0,0;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  4;10,10,11,11;,
  4;11,11,12,12;,
  4;12,12,13,13;,
  4;13,13,39,39;,
  4;39,39,40,40;,
  4;40,40,14,14;,
  4;14,14,15,15;,
  4;15,15,16,16;,
  4;16,16,17,17;,
  4;17,17,10,10;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  4;41,41,18,18;,
  4;18,18,19,19;,
  4;19,19,20,20;,
  4;20,20,21,21;,
  4;21,21,22,22;,
  4;22,22,23,23;,
  4;23,23,15,15;,
  4;15,15,24,24;,
  4;24,24,42,42;,
  4;42,42,41,41;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  4;25,25,26,26;,
  4;26,26,27,27;,
  4;27,27,28,28;,
  4;28,28,43,43;,
  4;43,43,44,44;,
  4;44,44,29,29;,
  4;29,29,30,30;,
  4;30,30,31,31;,
  4;31,31,32,32;,
  4;32,32,25,25;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  4;33,33,33,33;,
  3;34,34,34;,
  4;35,35,35,35;,
  4;45,45,45,45;,
  3;46,46,46;,
  3;36,36,36;,
  3;47,47,47;;
 }
 MeshTextureCoords {
  186;
  -0.004474;0.387962;,
  1.003616;0.386786;,
  1.003702;0.447930;,
  -0.004388;0.449106;,
  1.003788;0.509075;,
  -0.004302;0.510251;,
  1.003873;0.570219;,
  -0.004216;0.571395;,
  1.003959;0.631364;,
  -0.004131;0.632540;,
  1.004045;0.692508;,
  -0.004045;0.693684;,
  1.004131;0.753653;,
  -0.003959;0.754829;,
  1.004216;0.814797;,
  -0.003874;0.815973;,
  1.004302;0.875942;,
  -0.003788;0.877117;,
  1.004388;0.937086;,
  -0.003702;0.938262;,
  1.004474;0.998230;,
  -0.003616;0.999406;,
  0.514510;0.081701;,
  0.514510;0.134832;,
  0.483280;0.038716;,
  0.483280;0.177817;,
  0.432748;0.194235;,
  0.432748;0.022298;,
  0.382217;0.177817;,
  0.382217;0.038716;,
  0.350987;0.134832;,
  0.350987;0.081701;,
  0.186461;0.085490;,
  0.217691;0.042506;,
  0.186461;0.138622;,
  0.217691;0.181606;,
  0.268222;0.026087;,
  0.268222;0.198025;,
  0.318754;0.042506;,
  0.318754;0.181606;,
  0.349984;0.085490;,
  0.349984;0.138622;,
  -0.004474;0.387962;,
  1.003616;0.386786;,
  1.003702;0.447930;,
  -0.004388;0.449106;,
  1.003788;0.509075;,
  -0.004302;0.510251;,
  1.003873;0.570219;,
  -0.004216;0.571395;,
  1.003959;0.631364;,
  -0.004131;0.632540;,
  1.004045;0.692508;,
  -0.004045;0.693684;,
  1.004131;0.753653;,
  -0.003959;0.754829;,
  1.004216;0.814797;,
  -0.003874;0.815973;,
  1.004302;0.875942;,
  -0.003788;0.877117;,
  1.004388;0.937086;,
  -0.003702;0.938262;,
  1.004474;0.998230;,
  -0.003616;0.999406;,
  0.514510;0.081701;,
  0.514510;0.134832;,
  0.483280;0.038716;,
  0.483280;0.177817;,
  0.432748;0.022298;,
  0.432748;0.194235;,
  0.382217;0.177817;,
  0.382217;0.038716;,
  0.350987;0.134832;,
  0.350987;0.081701;,
  0.186461;0.085490;,
  0.217691;0.042506;,
  0.186461;0.138622;,
  0.217691;0.181606;,
  0.268222;0.026087;,
  0.268222;0.198025;,
  0.318754;0.042506;,
  0.318754;0.181606;,
  0.349984;0.085490;,
  0.349984;0.138622;,
  -0.004474;0.387962;,
  1.003616;0.386786;,
  1.003702;0.447930;,
  -0.004388;0.449106;,
  1.003788;0.509075;,
  -0.004302;0.510251;,
  1.003873;0.570219;,
  -0.004216;0.571395;,
  1.003959;0.631364;,
  -0.004131;0.632540;,
  1.004045;0.692508;,
  -0.004045;0.693684;,
  1.004131;0.753653;,
  -0.003959;0.754829;,
  1.004216;0.814797;,
  -0.003874;0.815973;,
  1.004302;0.875942;,
  -0.003788;0.877117;,
  1.004388;0.937086;,
  -0.003702;0.938262;,
  1.004474;0.998230;,
  -0.003616;0.999406;,
  0.514510;0.081701;,
  0.514510;0.134832;,
  0.483280;0.038716;,
  0.483280;0.177817;,
  0.432748;0.022298;,
  0.432748;0.194235;,
  0.382217;0.177817;,
  0.382217;0.038716;,
  0.350987;0.134832;,
  0.350987;0.081701;,
  0.186461;0.138622;,
  0.186461;0.085490;,
  0.217691;0.181606;,
  0.217691;0.042506;,
  0.268222;0.026087;,
  0.268222;0.198025;,
  0.318754;0.042506;,
  0.318754;0.181606;,
  0.349984;0.085490;,
  0.349984;0.138622;,
  -0.004474;0.387962;,
  1.003616;0.386786;,
  1.003702;0.447930;,
  -0.004388;0.449106;,
  1.003788;0.509075;,
  -0.004302;0.510251;,
  1.003873;0.570219;,
  -0.004216;0.571395;,
  1.003959;0.631364;,
  -0.004131;0.632540;,
  1.004045;0.692508;,
  -0.004045;0.693684;,
  1.004131;0.753653;,
  -0.003959;0.754829;,
  1.004216;0.814797;,
  -0.003874;0.815973;,
  1.004302;0.875942;,
  -0.003788;0.877117;,
  1.004388;0.937086;,
  -0.003702;0.938262;,
  1.004474;0.998230;,
  -0.003616;0.999406;,
  0.514510;0.081701;,
  0.514510;0.134832;,
  0.483280;0.038716;,
  0.483280;0.177817;,
  0.432748;0.194235;,
  0.432748;0.022298;,
  0.382217;0.177817;,
  0.382217;0.038716;,
  0.350987;0.134832;,
  0.350987;0.081701;,
  0.186461;0.085490;,
  0.217691;0.042506;,
  0.186461;0.138622;,
  0.217691;0.181606;,
  0.268222;0.026087;,
  0.268222;0.198025;,
  0.318754;0.042506;,
  0.318754;0.181606;,
  0.349984;0.085490;,
  0.349984;0.138622;,
  0.008993;0.363722;,
  0.009481;0.238220;,
  0.243851;0.238481;,
  0.243363;0.363983;,
  0.009031;0.088050;,
  0.242914;0.213813;,
  0.008543;0.213551;,
  0.008505;0.489224;,
  0.242875;0.489485;,
  0.479157;0.239265;,
  0.479119;0.364506;,
  0.244748;0.364244;,
  0.770848;0.094337;,
  0.770360;0.219839;,
  0.535989;0.219577;,
  0.803370;0.003512;,
  1.000157;0.200300;,
  0.803370;0.200300;;
 }
}
