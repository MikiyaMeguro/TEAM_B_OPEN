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
 73;
 13.06371;-0.04592;-9.39740;,
 -14.00720;-0.04592;-9.39740;,
 12.54084;3.89982;-8.06072;,
 12.30960;5.93203;-7.91209;,
 12.14793;7.35280;-7.80817;,
 8.14679;7.33103;-8.39680;,
 3.68247;6.89226;-8.39680;,
 -0.33732;7.51348;-8.39680;,
 -3.75831;7.95224;-8.39680;,
 -7.61694;7.33103;-8.39680;,
 -12.81447;5.18338;-7.96684;,
 -11.43082;7.35280;-7.80817;,
 -8.13894;7.42250;8.39680;,
 -7.86717;8.94514;-0.34647;,
 -13.06371;7.01038;-0.32541;,
 -12.14793;6.98861;7.80817;,
 12.82156;2.08219;8.24115;,
 12.37718;5.33812;7.95552;,
 13.06371;-0.04592;9.39740;,
 -13.06371;-0.04592;9.39740;,
 12.14793;7.35280;7.80817;,
 8.19573;7.33103;8.39680;,
 3.71458;7.33103;8.39680;,
 -1.00499;7.33103;8.39680;,
 -4.11664;7.95224;8.39680;,
 -8.13894;7.42250;8.39680;,
 -12.14793;6.98861;7.80817;,
 -12.41765;5.39001;7.98153;,
 13.06371;-0.04592;9.39740;,
 -13.06371;-0.04592;9.39740;,
 13.06371;-0.04592;0.72474;,
 13.06371;-0.04592;-9.39740;,
 -14.00720;-0.04592;-9.39740;,
 -13.57960;0.00059;-0.57264;,
 -13.06371;7.01038;-0.32541;,
 -14.48859;1.93251;-0.40016;,
 -12.41765;5.39001;7.98153;,
 -12.14793;6.98861;7.80817;,
 12.30960;5.93203;-7.91209;,
 14.57822;2.62638;-2.51195;,
 12.54084;3.89982;-8.06072;,
 13.06371;7.32611;1.59809;,
 8.40677;8.41275;1.61694;,
 8.19573;7.33103;8.39680;,
 12.14793;7.35280;7.80817;,
 3.69777;8.02237;4.19783;,
 3.71458;7.33103;8.39680;,
 -0.65622;9.07655;-0.37569;,
 -1.00499;7.33103;8.39680;,
 -3.92974;8.94514;-0.36242;,
 -4.11664;7.95224;8.39680;,
 12.14793;7.35280;-7.80817;,
 8.14679;7.33103;-8.39680;,
 3.68247;6.89226;-8.39680;,
 -0.33732;7.51348;-8.39680;,
 -3.75831;7.95224;-8.39680;,
 -7.61694;7.33103;-8.39680;,
 -11.43082;7.35280;-7.80817;,
 -12.81447;5.18338;-7.96684;,
 -11.43082;7.35280;-7.80817;,
 12.37718;5.33812;7.95552;,
 14.78957;2.99397;1.25255;,
 13.06371;7.32611;1.59809;,
 12.14793;7.35280;7.80817;,
 -14.00720;-0.04592;-9.39740;,
 -13.57960;0.00059;-0.57264;,
 -13.06371;-0.04592;9.39740;,
 13.06371;-0.04592;9.39740;,
 13.06371;-0.04592;0.72474;,
 14.78957;2.26749;1.12063;,
 12.82156;2.08219;8.24115;,
 13.06371;-0.04592;-9.39740;,
 12.14793;7.35280;-7.80817;;
 
 51;
 3;0,1,2;,
 3;2,1,3;,
 3;3,1,4;,
 3;4,1,5;,
 3;5,1,6;,
 3;6,1,7;,
 3;7,1,8;,
 3;8,1,9;,
 3;1,10,9;,
 3;10,11,9;,
 4;12,13,14,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;17,20,19;,
 3;20,21,19;,
 3;21,22,19;,
 3;22,23,19;,
 3;23,24,19;,
 3;24,25,19;,
 3;25,26,19;,
 3;26,27,19;,
 3;28,29,30;,
 3;30,29,31;,
 3;31,29,32;,
 3;29,33,32;,
 4;34,35,36,37;,
 3;38,39,40;,
 4;41,42,43,44;,
 4;43,42,45,46;,
 4;46,45,47,48;,
 4;48,47,49,50;,
 4;50,49,13,12;,
 4;51,52,42,41;,
 4;45,42,52,53;,
 4;47,45,53,54;,
 4;49,47,54,55;,
 4;13,49,55,56;,
 4;14,13,56,57;,
 4;58,35,34,59;,
 4;60,61,62,63;,
 4;64,65,35,58;,
 4;36,35,65,66;,
 4;67,68,69,70;,
 3;40,39,71;,
 3;71,39,68;,
 3;39,69,68;,
 3;38,72,39;,
 3;72,62,39;,
 3;62,61,39;,
 3;69,39,61;,
 4;70,69,61,60;;
 
 MeshMaterialList {
  1;
  51;
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
    "data\\TEXTURE\\UV\\Snowwall.jpg";
   }
  }
 }
 MeshNormals {
  66;
  0.000000;0.320854;-0.947129;,
  0.000287;0.117291;-0.993097;,
  0.091417;-0.110591;-0.989653;,
  -0.149472;0.166617;-0.974627;,
  0.093123;-0.104642;0.990141;,
  -0.241291;0.964776;0.104812;,
  0.994619;-0.066061;0.079799;,
  0.002265;0.102440;0.994737;,
  0.073229;-0.076157;0.994403;,
  0.063139;-0.054450;-0.996518;,
  0.000000;0.134408;0.990926;,
  -0.001336;0.146075;-0.989273;,
  0.010155;0.118083;0.992952;,
  0.014801;0.104856;-0.994377;,
  0.000596;0.123480;0.992347;,
  -0.005682;0.131299;-0.991326;,
  -0.153436;0.980497;0.122813;,
  -0.125987;0.208826;-0.969803;,
  0.121992;0.992413;0.015285;,
  0.033268;0.999164;0.023779;,
  0.035468;0.998991;0.027548;,
  0.094485;0.995461;0.011422;,
  -0.005776;0.999969;-0.005297;,
  -0.145490;0.989323;-0.008539;,
  -0.493354;0.868292;-0.051679;,
  -0.981825;-0.184699;0.043655;,
  0.297513;-0.953938;-0.038586;,
  -0.175963;0.234444;-0.956072;,
  -0.994601;0.102014;0.019041;,
  -0.978774;0.092273;0.182993;,
  0.974997;0.144183;0.169094;,
  0.981778;0.172809;0.079048;,
  0.019494;0.200652;-0.979469;,
  0.038677;0.077268;-0.996260;,
  0.985298;0.022285;-0.169384;,
  0.976628;-0.206853;0.058392;,
  0.988735;-0.025846;0.147431;,
  0.000000;0.258690;0.965960;,
  0.020127;0.168803;0.985444;,
  -0.093048;0.192243;0.976926;,
  -0.166251;0.237840;0.956970;,
  -0.954768;0.207194;0.213280;,
  -0.982845;-0.090567;0.160666;,
  0.000000;-1.000000;0.000000;,
  -0.978429;-0.206437;0.007798;,
  -0.967839;0.221884;0.118554;,
  0.940036;0.130028;-0.315317;,
  0.936437;0.176139;-0.303414;,
  0.063099;0.989823;0.127552;,
  0.123616;0.987828;0.094421;,
  0.008931;0.985447;0.169751;,
  0.047094;0.984761;0.167413;,
  0.007142;0.988977;0.147898;,
  0.119601;0.990760;-0.063947;,
  0.002906;0.996730;-0.080755;,
  0.061658;0.991157;-0.117496;,
  0.139538;0.979463;-0.145536;,
  -0.018548;0.987224;-0.158256;,
  -0.135042;0.980980;-0.139432;,
  -0.613967;0.777288;-0.137360;,
  -0.983261;0.162393;-0.082616;,
  0.943209;0.332199;0.000005;,
  0.955271;0.236767;0.177196;,
  0.921686;-0.384171;0.053912;,
  0.976473;-0.147072;-0.157703;,
  0.944675;0.256115;-0.204925;;
  51;
  3;0,1,32;,
  3;32,1,33;,
  3;33,1,2;,
  3;2,1,9;,
  3;9,1,11;,
  3;11,1,13;,
  3;13,1,15;,
  3;15,1,17;,
  3;1,27,17;,
  3;27,3,17;,
  4;16,23,24,5;,
  3;36,30,6;,
  3;37,38,7;,
  3;38,4,7;,
  3;4,8,7;,
  3;8,10,7;,
  3;10,12,7;,
  3;12,14,7;,
  3;14,39,7;,
  3;39,40,7;,
  3;41,29,42;,
  3;43,43,26;,
  3;26,43,43;,
  3;43,43,43;,
  3;42,25,44;,
  4;45,28,29,41;,
  3;46,34,47;,
  4;18,19,48,49;,
  4;48,19,20,50;,
  4;50,20,21,51;,
  4;51,21,22,52;,
  4;52,22,23,16;,
  4;53,54,19,18;,
  4;20,19,54,55;,
  4;21,20,55,56;,
  4;22,21,56,57;,
  4;23,22,57,58;,
  4;24,23,58,59;,
  4;60,28,24,59;,
  4;30,31,61,62;,
  4;44,25,28,60;,
  4;29,28,25,42;,
  4;6,63,35,36;,
  3;47,34,64;,
  3;64,34,63;,
  3;34,35,26;,
  3;46,65,34;,
  3;65,61,34;,
  3;61,31,34;,
  3;35,34,31;,
  4;36,35,31,30;;
 }
 MeshTextureCoords {
  73;
  0.613133;0.874957;,
  0.851084;0.874957;,
  0.613133;0.739098;,
  0.613133;0.679013;,
  0.613133;0.637006;,
  0.657913;0.637006;,
  0.698571;0.637006;,
  0.735180;0.637006;,
  0.766337;0.637006;,
  0.801479;0.637006;,
  0.851084;0.701148;,
  0.851084;0.637006;,
  0.807602;0.000687;,
  0.797331;0.284525;,
  0.993728;0.283842;,
  0.993728;0.000687;,
  0.613133;0.704867;,
  0.613133;0.820331;,
  0.613133;0.641946;,
  0.851084;0.641946;,
  0.613133;0.879898;,
  0.652933;0.879898;,
  0.698278;0.879898;,
  0.741261;0.879898;,
  0.769600;0.879898;,
  0.806233;0.879898;,
  0.851084;0.879898;,
  0.851084;0.809817;,
  0.613133;0.882369;,
  0.851084;0.882369;,
  0.613133;0.773662;,
  0.613133;0.644417;,
  0.851084;0.644417;,
  0.851084;0.755279;,
  0.735955;0.637006;,
  0.734896;0.708950;,
  0.859542;0.707087;,
  0.859542;0.637006;,
  0.853781;0.679013;,
  0.782675;0.734362;,
  0.853781;0.739098;,
  0.006272;0.287278;,
  0.182276;0.286666;,
  0.171435;0.000687;,
  0.006272;0.000687;,
  0.360247;0.286046;,
  0.359612;0.000687;,
  0.524801;0.285474;,
  0.537983;0.000687;,
  0.648520;0.285043;,
  0.655584;0.000687;,
  0.006272;0.545868;,
  0.192101;0.545868;,
  0.360825;0.545868;,
  0.512749;0.545868;,
  0.642041;0.545868;,
  0.787874;0.545868;,
  0.993728;0.545868;,
  0.621590;0.701148;,
  0.621590;0.637006;,
  0.615829;0.696573;,
  0.734435;0.731150;,
  0.740915;0.637006;,
  0.615829;0.637006;,
  0.621590;0.874957;,
  0.732452;0.874957;,
  0.859542;0.874957;,
  0.615829;0.874957;,
  0.724535;0.874957;,
  0.731961;0.767094;,
  0.615829;0.812037;,
  0.853781;0.874957;,
  0.853781;0.637006;;
 }
}
