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
 64;
 -7.39076;12.51264;-5.83213;,
 -10.02747;13.50774;-4.42524;,
 -5.97717;18.69571;-4.56834;,
 -4.40925;16.33164;-5.93745;,
 0.35012;20.51263;-4.63604;,
 0.24845;17.66912;-5.98729;,
 6.53761;18.26446;-4.60248;,
 4.80322;16.01419;-5.96259;,
 10.22189;12.80996;-4.48049;,
 7.51532;11.99899;-5.87279;,
 9.99568;6.23254;-4.31665;,
 7.34879;7.15718;-5.75217;,
 5.94540;1.04457;-4.17355;,
 4.36727;3.33818;-5.64684;,
 -0.38190;-0.77234;-4.10585;,
 -0.29041;2.00071;-5.59701;,
 -6.56939;1.47581;-4.13942;,
 -4.84518;3.65563;-5.62172;,
 -10.25368;6.93031;-4.26141;,
 -7.55728;7.67084;-5.71151;,
 -10.02747;13.50774;-4.42524;,
 -7.39076;12.51264;-5.83213;,
 7.55681;12.28611;5.71152;,
 4.84471;16.30131;5.62172;,
 7.39029;7.44431;5.83213;,
 4.40876;3.62530;5.93745;,
 0.28994;17.95624;5.59701;,
 -0.24892;2.28783;5.98729;,
 -4.36774;16.61877;5.64684;,
 -4.80369;3.94276;5.96259;,
 -7.34928;12.79977;5.75217;,
 -7.51578;7.95796;5.87279;,
 7.34879;7.15718;-5.75217;,
 4.36727;3.33818;-5.64684;,
 7.51532;11.99899;-5.87279;,
 4.80322;16.01419;-5.96259;,
 -0.29041;2.00071;-5.59701;,
 0.24845;17.66912;-5.98729;,
 -4.84518;3.65563;-5.62172;,
 -4.40925;16.33164;-5.93745;,
 -7.55728;7.67084;-5.71151;,
 -7.39076;12.51264;-5.83213;,
 -9.99567;13.72776;4.45202;,
 -5.94538;18.91575;4.30892;,
 0.38192;20.73266;4.24123;,
 6.56941;18.48449;4.27479;,
 10.25369;13.02999;4.39679;,
 10.02748;6.45257;4.56062;,
 5.97720;1.26459;4.70372;,
 -0.35010;-0.55232;4.77142;,
 -6.53759;1.69584;4.73785;,
 -10.22188;7.15034;4.61585;,
 -9.99567;13.72776;4.45202;,
 -7.34928;12.79977;5.75217;,
 -4.36774;16.61877;5.64684;,
 0.28994;17.95624;5.59701;,
 4.84471;16.30131;5.62172;,
 7.55681;12.28611;5.71152;,
 7.39029;7.44431;5.83213;,
 4.40876;3.62530;5.93745;,
 -0.24892;2.28783;5.98729;,
 -4.80369;3.94276;5.96259;,
 -7.51578;7.95796;5.87279;,
 -7.34928;12.79977;5.75217;;
 
 46;
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
 3;24,23,25;,
 3;23,26,25;,
 3;25,26,27;,
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
 4;2,1,42,43;,
 4;4,2,43,44;,
 4;6,4,44,45;,
 4;8,6,45,46;,
 4;10,8,46,47;,
 4;12,10,47,48;,
 4;14,12,48,49;,
 4;16,14,49,50;,
 4;18,16,50,51;,
 4;20,18,51,52;,
 4;43,42,53,54;,
 4;44,43,54,55;,
 4;45,44,55,56;,
 4;46,45,56,57;,
 4;47,46,57,58;,
 4;48,47,58,59;,
 4;49,48,59,60;,
 4;50,49,60,61;,
 4;51,50,61,62;,
 4;52,51,62,63;;
 
 MeshMaterialList {
  1;
  46;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\Wheel.jpg";
   }
  }
 }
 MeshNormals {
  50;
  -0.195726;0.096602;0.975889;,
  -0.091193;0.164654;0.982127;,
  0.009345;0.193524;0.981051;,
  0.107660;0.157802;0.981584;,
  0.274786;0.101689;0.956113;,
  0.202725;-0.048172;0.978050;,
  0.098250;-0.115813;0.988400;,
  -0.002287;-0.144683;0.989475;,
  -0.100603;-0.108961;0.988942;,
  -0.267913;-0.054149;0.961920;,
  -0.292217;0.081357;-0.952885;,
  -0.106601;0.128256;-0.985995;,
  0.002810;0.159674;-0.987166;,
  0.109802;0.120799;-0.986586;,
  0.218304;0.039577;-0.975078;,
  0.285406;-0.128517;-0.949751;,
  0.099563;-0.176965;-0.979168;,
  -0.009848;-0.208382;-0.977998;,
  -0.116841;-0.169507;-0.978578;,
  -0.225270;-0.087796;-0.970333;,
  -0.427391;0.132017;-0.894376;,
  -0.255779;0.351834;-0.900439;,
  0.012312;0.428817;-0.903307;,
  0.274480;0.333562;-0.901885;,
  0.430585;0.102450;-0.896716;,
  0.421001;-0.176239;-0.889774;,
  0.249388;-0.396055;-0.883711;,
  -0.018703;-0.473039;-0.880843;,
  -0.280870;-0.377783;-0.882265;,
  -0.436975;-0.146672;-0.887435;,
  -0.939871;0.341493;-0.005098;,
  -0.559636;0.828531;-0.018532;,
  0.034361;0.999100;-0.024887;,
  0.615233;0.788046;-0.021736;,
  0.961107;0.275985;-0.010283;,
  0.939871;-0.341492;0.005097;,
  0.559637;-0.828531;0.018531;,
  -0.034360;-0.999100;0.024886;,
  -0.615232;-0.788046;0.021736;,
  -0.961107;-0.275986;0.010283;,
  -0.229611;0.367286;0.901321;,
  -0.387829;0.164628;0.906910;,
  0.017554;0.438261;0.898676;,
  0.259258;0.350441;0.899987;,
  0.403179;0.137371;0.904752;,
  0.394342;-0.119566;0.911152;,
  0.236123;-0.322224;0.916743;,
  -0.011042;-0.393199;0.919387;,
  -0.252746;-0.305380;0.918075;,
  -0.396667;-0.092309;0.913310;;
  46;
  4;10,20,21,11;,
  4;11,21,22,12;,
  4;12,22,23,13;,
  4;13,23,24,14;,
  4;14,24,25,15;,
  4;15,25,26,16;,
  4;16,26,27,17;,
  4;17,27,28,18;,
  4;18,28,29,19;,
  4;19,29,20,10;,
  3;4,3,5;,
  3;5,3,6;,
  3;3,2,6;,
  3;6,2,7;,
  3;2,1,7;,
  3;7,1,8;,
  3;1,0,8;,
  3;0,9,8;,
  3;15,16,14;,
  3;14,16,13;,
  3;16,17,13;,
  3;13,17,12;,
  3;17,18,12;,
  3;12,18,11;,
  3;18,19,11;,
  3;19,10,11;,
  4;31,30,30,31;,
  4;32,31,31,32;,
  4;33,32,32,33;,
  4;34,33,33,34;,
  4;35,34,34,35;,
  4;36,35,35,36;,
  4;37,36,36,37;,
  4;38,37,37,38;,
  4;39,38,38,39;,
  4;30,39,39,30;,
  4;40,41,0,1;,
  4;42,40,1,2;,
  4;43,42,2,3;,
  4;44,43,3,4;,
  4;45,44,4,5;,
  4;46,45,5,6;,
  4;47,46,6,7;,
  4;48,47,7,8;,
  4;49,48,8,9;,
  4;41,49,9,0;;
 }
 MeshTextureCoords {
  64;
  0.998427;0.750227;,
  0.996465;0.802788;,
  0.897169;0.802753;,
  0.899130;0.750193;,
  0.797872;0.802718;,
  0.799833;0.750158;,
  0.698575;0.802684;,
  0.700536;0.750123;,
  0.599277;0.802649;,
  0.601239;0.750088;,
  0.499980;0.802614;,
  0.501942;0.750053;,
  0.400683;0.802579;,
  0.402645;0.750019;,
  0.301386;0.802544;,
  0.303347;0.749984;,
  0.202089;0.802509;,
  0.204051;0.749949;,
  0.102792;0.802475;,
  0.104753;0.749914;,
  0.003495;0.802440;,
  0.005456;0.749879;,
  0.641112;0.228485;,
  0.679637;0.175461;,
  0.641112;0.294027;,
  0.679637;0.347052;,
  0.741971;0.155207;,
  0.741971;0.367305;,
  0.804305;0.175461;,
  0.804305;0.347052;,
  0.842830;0.228485;,
  0.842830;0.294027;,
  0.166301;0.232684;,
  0.204826;0.179659;,
  0.166301;0.298226;,
  0.204826;0.351250;,
  0.267160;0.159405;,
  0.267160;0.371504;,
  0.329494;0.179659;,
  0.329494;0.351250;,
  0.368019;0.232684;,
  0.368019;0.298226;,
  0.995405;0.999889;,
  0.896107;0.999855;,
  0.796810;0.999820;,
  0.697513;0.999785;,
  0.598216;0.999750;,
  0.498919;0.999715;,
  0.399622;0.999681;,
  0.300325;0.999646;,
  0.201028;0.999611;,
  0.101732;0.999576;,
  0.002434;0.999541;,
  0.994543;1.044528;,
  0.895246;1.044494;,
  0.795949;1.044459;,
  0.696652;1.044424;,
  0.597355;1.044389;,
  0.498058;1.044354;,
  0.398761;1.044320;,
  0.299464;1.044285;,
  0.200167;1.044250;,
  0.100870;1.044215;,
  0.001573;1.044180;;
 }
}
