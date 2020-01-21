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
 104;
 3.77450;3.10460;-7.66918;,
 2.99447;-0.14235;-9.81230;,
 -8.33177;-0.14235;-5.68990;,
 -7.55173;3.10460;-3.54678;,
 -4.71247;6.65177;4.42081;,
 6.72096;6.65177;0.25937;,
 4.50079;4.28917;-5.84053;,
 -6.93267;4.28927;-1.67913;,
 9.03096;5.37570;4.11395;,
 7.66376;6.83904;1.83294;,
 -4.42323;6.83905;6.23224;,
 -4.00436;5.37571;8.85842;,
 5.97950;-0.89402;-5.10219;,
 8.61460;1.91031;2.13771;,
 -4.95571;1.91031;7.07690;,
 -7.59073;-0.89468;-0.16277;,
 -9.69988;3.54784;-1.46897;,
 -11.85761;1.41586;0.14216;,
 -9.02206;4.43341;7.93280;,
 -6.86432;6.56538;6.32168;,
 9.32184;6.56561;0.43031;,
 11.96290;3.86968;0.51325;,
 9.12734;0.85215;-7.27739;,
 6.48628;3.54806;-7.36033;,
 2.99447;-0.14235;-9.81230;,
 5.28193;-1.03460;-6.61461;,
 -8.02862;-1.03461;-1.76997;,
 -8.33177;-0.14235;-5.68990;,
 -9.18460;-0.59144;-0.05326;,
 -6.34904;2.42611;7.73738;,
 8.80536;2.69931;3.02087;,
 -4.53416;2.69932;7.87605;,
 9.83715;2.42598;1.84614;,
 7.00159;-0.59156;-5.94450;,
 4.50079;4.28917;-5.84053;,
 3.77450;3.10460;-7.66918;,
 -7.55173;3.10460;-3.54678;,
 -6.93267;4.28927;-1.67913;,
 -14.52695;-1.16823;-3.57047;,
 -11.15566;2.11290;-2.56404;,
 -10.54575;-0.76294;-1.51763;,
 5.28193;-1.03460;-6.61461;,
 -8.02862;-1.03461;-1.76997;,
 7.10310;-0.76371;-7.94100;,
 8.67123;-0.89610;-12.20374;,
 6.89742;2.11437;-9.13540;,
 7.00159;-0.59156;-5.94450;,
 5.97950;-0.89402;-5.10219;,
 5.28193;-1.03460;-6.61461;,
 7.10310;-0.76371;-7.94100;,
 9.83715;2.42598;1.84614;,
 8.61460;1.91031;2.13771;,
 14.20109;5.07913;3.23043;,
 9.03096;5.37570;4.11395;,
 8.80536;2.69931;3.02087;,
 10.92909;3.30770;2.57085;,
 10.81103;6.27971;1.61717;,
 7.66376;6.83904;1.83294;,
 9.03096;5.37570;4.11395;,
 14.20109;5.07913;3.23043;,
 6.48628;3.54806;-7.36033;,
 4.50079;4.28917;-5.84053;,
 6.72096;6.65177;0.25937;,
 9.32184;6.56561;0.43031;,
 3.77450;3.10460;-7.66918;,
 4.50079;4.28917;-5.84053;,
 6.48628;3.54806;-7.36033;,
 2.99447;-0.14235;-9.81230;,
 5.28193;-1.03460;-6.61461;,
 -4.53416;2.69932;7.87605;,
 -4.00436;5.37571;8.85842;,
 -8.71300;6.71714;11.37630;,
 -6.71968;3.30784;8.99441;,
 -7.59073;-0.89468;-0.16277;,
 -4.95571;1.91031;7.07690;,
 -6.34904;2.42611;7.73738;,
 -9.18460;-0.59144;-0.05326;,
 -8.02862;-1.03461;-1.76997;,
 -10.54575;-0.76294;-1.51763;,
 -8.33177;-0.14235;-5.68990;,
 -8.02862;-1.03461;-1.76997;,
 -7.55173;3.10460;-3.54678;,
 -6.93267;4.28927;-1.67913;,
 -9.69988;3.54784;-1.46897;,
 -6.86432;6.56538;6.32168;,
 -4.71247;6.65177;4.42081;,
 -6.93267;4.28927;-1.67913;,
 -9.69988;3.54784;-1.46897;,
 -4.00436;5.37571;8.85842;,
 -4.42323;6.83905;6.23224;,
 -7.24221;6.27952;8.18809;,
 -8.71300;6.71714;11.37630;,
 10.92909;3.30770;2.57085;,
 8.80536;2.69931;3.02087;,
 -4.53416;2.69932;7.87605;,
 -6.71968;3.30784;8.99441;,
 -6.71968;3.30784;8.99441;,
 -8.71300;6.71714;11.37630;,
 -7.24221;6.27952;8.18809;,
 6.72096;6.65177;0.25937;,
 -4.71247;6.65177;4.42081;,
 14.20109;5.07913;3.23043;,
 10.81103;6.27971;1.61717;,
 10.92909;3.30770;2.57085;;
 
 42;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;17,28,29,18;,
 4;30,8,11,31;,
 4;21,32,33,22;,
 4;34,35,36,37;,
 4;38,17,16,39;,
 4;40,28,17,38;,
 4;41,12,15,42;,
 4;22,33,43,44;,
 4;23,22,44,45;,
 4;46,47,48,49;,
 4;50,51,47,46;,
 4;52,53,54,55;,
 4;56,57,58,59;,
 4;60,61,62,63;,
 4;45,64,65,66;,
 4;44,67,64,45;,
 4;43,68,67,44;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,73,76,78;,
 4;79,80,40,38;,
 4;81,79,38,39;,
 4;82,81,39,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,51,50;,
 4;14,13,30,31;,
 4;75,74,94,95;,
 4;18,29,96,97;,
 4;19,18,97,98;,
 4;89,85,84,90;,
 4;9,99,100,10;,
 4;63,62,57,56;,
 4;101,21,20,102;,
 4;103,32,21,101;;
 
 MeshMaterialList {
  1;
  42;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\Makura.jpg";
   }
  }
 }
 MeshNormals {
  59;
  0.256480;-0.966295;0.022160;,
  -0.183062;-0.956816;0.225813;,
  0.140779;0.769194;-0.623315;,
  -0.488542;0.753590;-0.439806;,
  0.136526;0.972185;0.190310;,
  0.053685;0.989850;0.131586;,
  0.410151;-0.751358;0.516949;,
  -0.053395;-0.695156;0.716874;,
  0.266646;-0.963649;0.016732;,
  -0.578466;0.709286;-0.402853;,
  0.338823;-0.388557;0.856868;,
  0.424639;-0.742973;0.517371;,
  0.345528;0.810410;-0.473123;,
  -0.521593;0.828998;-0.201751;,
  -0.704416;0.709757;-0.006549;,
  -0.302404;-0.853544;0.424281;,
  0.466374;-0.876184;0.121646;,
  0.651066;0.642636;-0.403896;,
  0.025358;-0.997842;-0.060566;,
  0.204481;-0.965911;0.158756;,
  0.291831;-0.606380;0.739688;,
  0.160832;0.880622;0.445688;,
  0.103147;0.976298;0.190270;,
  -0.077006;0.892140;-0.445147;,
  -0.187408;0.724270;-0.663560;,
  -0.246237;0.587156;-0.771113;,
  0.192938;0.916715;0.349868;,
  0.244407;-0.589755;0.769710;,
  -0.032899;-0.968858;0.245421;,
  -0.044287;-0.998583;-0.029490;,
  -0.316796;0.576705;-0.753028;,
  -0.285549;0.719305;-0.633294;,
  -0.220093;0.892293;-0.394172;,
  0.061341;0.985134;0.160459;,
  0.495745;-0.841684;0.214023;,
  0.294229;-0.857060;0.422940;,
  0.067953;-0.859199;0.507109;,
  -0.296066;-0.810362;0.505626;,
  -0.701819;0.702847;-0.115999;,
  -0.467995;0.875024;-0.123750;,
  -0.134581;0.976811;-0.166517;,
  0.003251;0.975926;-0.218077;,
  0.365112;0.832320;-0.417058;,
  0.595192;0.583343;-0.552682;,
  -0.083359;-0.981033;-0.175002;,
  -0.036074;-0.983018;-0.179928;,
  -0.448903;-0.712426;0.539384;,
  -0.529452;-0.719325;0.449725;,
  0.261652;-0.420008;0.868983;,
  0.327522;-0.385024;0.862836;,
  0.567920;-0.820493;0.065251;,
  0.590187;-0.797035;0.128119;,
  -0.211415;-0.942246;0.259760;,
  0.256915;0.727897;-0.635736;,
  0.154404;0.888640;0.431832;,
  0.215840;0.947676;0.235207;,
  -0.549169;-0.714514;0.433456;,
  -0.687946;0.693045;-0.215450;,
  0.546515;0.550341;-0.631226;;
  42;
  4;24,25,30,31;,
  4;40,41,23,32;,
  4;21,22,33,26;,
  4;19,35,36,28;,
  4;13,14,38,39;,
  4;42,43,17,12;,
  4;44,18,29,45;,
  4;46,15,37,47;,
  4;20,48,49,27;,
  4;50,34,16,51;,
  4;23,24,31,32;,
  4;9,14,13,3;,
  4;1,15,46,52;,
  4;18,19,28,29;,
  4;51,16,0,8;,
  4;12,17,53,2;,
  4;16,19,18,0;,
  4;34,35,19,16;,
  4;11,48,20,6;,
  4;4,22,21,54;,
  4;12,23,41,42;,
  4;2,24,23,12;,
  4;53,25,24,2;,
  4;0,18,44,8;,
  4;27,49,10,7;,
  4;28,36,37,15;,
  4;29,28,15,1;,
  4;45,29,1,52;,
  4;31,30,9,3;,
  4;32,31,3,13;,
  4;39,40,32,13;,
  4;26,33,5,55;,
  4;6,20,35,34;,
  4;36,35,20,27;,
  4;37,36,27,7;,
  4;47,37,7,56;,
  4;39,38,57,57;,
  4;33,40,39,5;,
  4;22,41,40,33;,
  4;42,41,22,4;,
  4;58,43,42,58;,
  4;6,34,50,11;;
 }
 MeshTextureCoords {
  104;
  0.385150;0.482580;,
  0.385150;0.441637;,
  0.610690;0.441637;,
  0.610690;0.482580;,
  0.610690;0.535525;,
  0.385150;0.535525;,
  0.385150;0.471221;,
  0.610690;0.471221;,
  0.385149;0.540943;,
  0.385150;0.500000;,
  0.610690;0.500000;,
  0.610690;0.540943;,
  0.385149;0.649702;,
  0.385150;0.585399;,
  0.610690;0.585399;,
  0.610690;0.649702;,
  0.654675;0.250000;,
  0.654675;0.121369;,
  0.856700;0.121369;,
  0.856700;0.250000;,
  0.143300;0.250000;,
  0.143300;0.121369;,
  0.345325;0.121369;,
  0.345325;0.250000;,
  0.385150;0.379483;,
  0.385150;0.340852;,
  0.610690;0.340852;,
  0.610690;0.379483;,
  0.654675;0.000000;,
  0.856700;0.000000;,
  0.385150;0.579574;,
  0.610690;0.579574;,
  0.143300;0.000000;,
  0.345325;0.000000;,
  0.385150;0.441686;,
  0.385150;0.432240;,
  0.610690;0.432240;,
  0.610690;0.441686;,
  0.625000;0.121369;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.385150;0.659148;,
  0.610690;0.659148;,
  0.375000;0.000000;,
  0.375000;0.121369;,
  0.375000;0.250000;,
  0.375000;0.970325;,
  0.385149;0.970325;,
  0.385150;1.000000;,
  0.375000;1.000000;,
  0.375000;0.768300;,
  0.385150;0.768300;,
  0.375000;0.759527;,
  0.385149;0.759527;,
  0.385150;0.880895;,
  0.375000;0.880895;,
  0.375000;0.181290;,
  0.385150;0.181290;,
  0.385149;0.270637;,
  0.375000;0.270637;,
  0.375000;0.028255;,
  0.385150;0.028255;,
  0.385150;0.168580;,
  0.375000;0.168580;,
  0.385150;0.250000;,
  0.385150;0.279675;,
  0.375000;0.279675;,
  0.385150;0.121369;,
  0.385150;0.000000;,
  0.610690;0.880895;,
  0.610690;0.759527;,
  0.625000;0.759527;,
  0.625000;0.880895;,
  0.610690;0.970325;,
  0.610690;0.768300;,
  0.625000;0.768300;,
  0.625000;0.970325;,
  0.610690;1.000000;,
  0.625000;1.000000;,
  0.610690;0.121369;,
  0.610690;0.000000;,
  0.610690;0.250000;,
  0.610690;0.279675;,
  0.625000;0.279675;,
  0.625000;0.168580;,
  0.610690;0.168580;,
  0.610690;0.028255;,
  0.625000;0.028255;,
  0.610690;0.270637;,
  0.610690;0.181290;,
  0.625000;0.181290;,
  0.625000;0.270637;,
  0.375000;0.750000;,
  0.385150;0.750000;,
  0.610690;0.750000;,
  0.625000;0.750000;,
  0.875000;0.000000;,
  0.875000;0.121369;,
  0.875000;0.250000;,
  0.385150;0.494175;,
  0.610690;0.494175;,
  0.125000;0.121369;,
  0.125000;0.250000;,
  0.125000;0.000000;;
 }
}
