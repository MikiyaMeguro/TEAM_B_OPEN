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
 148;
 0.21437;-0.20686;2.85261;,
 1.55743;-0.20528;2.62517;,
 0.18673;-0.20409;2.09519;,
 1.24347;-0.20451;2.18900;,
 1.16562;-0.20289;1.92280;,
 3.18127;-0.31356;2.01005;,
 3.95374;-0.19671;0.96947;,
 2.65231;-0.19667;0.93491;,
 2.44727;-0.20127;1.68674;,
 2.74575;-0.18318;-1.28632;,
 2.70665;-0.18883;-0.35701;,
 3.66613;-0.18746;-0.56114;,
 3.28461;-0.29190;-1.55646;,
 1.08056;-0.18313;-1.33578;,
 2.89899;-0.14913;-2.02539;,
 0.05446;-0.17894;-2.05249;,
 0.08461;-0.18353;-1.29126;,
 -3.04064;-0.29465;-1.25684;,
 -3.85019;-0.20010;1.33843;,
 -2.86022;-0.19908;1.19667;,
 -2.76748;-0.18559;-1.02430;,
 -2.29126;-0.20334;1.91075;,
 -2.96596;-0.31554;2.47187;,
 -2.47570;-0.19537;-1.90852;,
 -1.68974;-0.18724;-1.16368;,
 -1.23806;-0.18448;-1.16840;,
 -1.12257;-0.17955;-1.97905;,
 -1.10351;-0.20377;2.01199;,
 -1.68497;-0.20719;2.86042;,
 0.21882;-1.30698;2.83944;,
 -1.73272;-1.15034;2.87521;,
 -1.87062;-2.12765;2.92597;,
 0.22852;-2.08561;2.83399;,
 1.73253;-2.05567;2.76831;,
 1.68490;-1.27697;2.71956;,
 3.35514;-2.20366;2.32682;,
 4.21302;-2.11149;0.79385;,
 4.17671;-1.19422;0.86181;,
 3.33338;-1.23671;2.25286;,
 3.27909;-1.54758;-1.94036;,
 3.87043;-1.36239;-0.85132;,
 3.89743;-2.31253;-1.04138;,
 3.48305;-2.44234;-2.21705;,
 0.06677;-1.40930;-2.19300;,
 2.76286;-1.55266;-2.19178;,
 2.82033;-2.37897;-2.31391;,
 0.10304;-3.17253;-2.30644;,
 0.05446;-0.17894;-2.05249;,
 -1.12257;-0.17955;-1.97905;,
 -2.42780;-1.45724;-2.17559;,
 -2.47570;-0.19537;-1.90852;,
 -2.46909;-1.06855;-2.18428;,
 -3.18373;-2.45914;-1.90300;,
 -4.12843;-2.13729;1.16126;,
 -4.08878;-1.35883;1.23839;,
 -3.17886;-1.48203;-1.63641;,
 -3.11720;-1.36533;2.54675;,
 -3.19446;-2.34392;2.73835;,
 1.16562;-0.20289;1.92280;,
 3.28461;-0.29190;-1.55646;,
 2.74575;-0.18318;-1.28632;,
 3.48305;-2.44234;-2.21705;,
 2.82033;-2.37897;-2.31391;,
 2.76286;-1.55266;-2.19178;,
 3.27909;-1.54758;-1.94036;,
 -2.46909;-1.06855;-2.18428;,
 -3.04064;-0.29465;-1.25684;,
 -2.42780;-1.45724;-2.17559;,
 -3.17886;-1.48203;-1.63641;,
 -2.76748;-0.18559;-1.02430;,
 -2.33416;-0.21739;2.80907;,
 -1.68412;-0.20356;1.96250;,
 -2.54628;-2.13815;2.79923;,
 -2.54098;-1.36085;2.89048;,
 -1.62214;-4.01173;2.95822;,
 -1.42469;-4.96120;2.89721;,
 0.15366;-4.95627;2.90953;,
 0.18964;-4.00031;3.00383;,
 -2.22469;-4.91252;2.60483;,
 -2.60472;-4.06246;2.73381;,
 -3.53166;-4.12474;1.00788;,
 -2.86567;-4.79654;0.90514;,
 -2.32479;-4.81548;-1.56790;,
 -2.64414;-4.23779;-2.13433;,
 -2.64414;-4.23779;-2.13433;,
 -1.44518;-4.12844;-2.39176;,
 -1.45450;-4.81749;-1.75981;,
 -2.32479;-4.81548;-1.56790;,
 -1.12833;-4.81599;-1.79135;,
 1.20294;-4.10070;-2.50397;,
 1.06797;-4.81946;-1.88828;,
 0.00454;-4.81576;-1.85848;,
 0.02932;-4.09597;-2.47464;,
 2.37119;-4.78798;-1.81877;,
 2.89431;-4.06800;-2.37393;,
 2.89431;-4.06800;-2.37393;,
 3.24706;-4.06276;-1.18215;,
 2.55517;-4.78281;-0.79525;,
 2.37119;-4.78798;-1.81877;,
 2.34178;-4.91973;2.40331;,
 2.81095;-4.77562;0.62768;,
 3.52490;-3.90257;0.68822;,
 2.80099;-4.07147;2.57271;,
 1.49205;-4.01406;2.87401;,
 1.30876;-4.96437;2.85853;,
 1.18379;-0.19734;1.00921;,
 -2.40159;-0.19922;1.23076;,
 -1.64680;-0.19869;1.16067;,
 1.16562;-0.20289;1.92280;,
 0.21410;-0.19774;1.05169;,
 1.12375;-0.18908;-0.35470;,
 2.70665;-0.18883;-0.35701;,
 0.26011;-0.18708;-0.70318;,
 -1.80708;-3.24533;2.97458;,
 -2.84208;-3.24642;2.89331;,
 0.18902;-3.24643;2.93599;,
 1.62207;-3.24666;2.81693;,
 3.26164;-3.24878;2.61265;,
 3.90838;-3.23978;0.73737;,
 3.61364;-3.22841;-1.12380;,
 3.23013;-3.16320;-2.31263;,
 3.23013;-3.16320;-2.31263;,
 2.63854;-3.16421;-2.43468;,
 2.63854;-3.16421;-2.43468;,
 0.05764;-3.78233;-2.40088;,
 -1.99998;-3.25536;-2.29575;,
 -2.35286;-2.43211;-2.18373;,
 -1.99998;-3.25536;-2.29575;,
 -3.02611;-3.16111;-1.96876;,
 -2.35286;-2.43211;-2.18373;,
 -2.46603;-2.44600;-2.09059;,
 -3.18373;-2.45914;-1.90300;,
 -3.94744;-3.23681;1.10877;,
 -2.77617;-3.48473;2.88889;,
 -2.64414;-4.23779;-2.13433;,
 -2.91011;-4.02499;-2.04271;,
 -3.02611;-3.16111;-1.96876;,
 -1.16413;-0.19836;1.11788;,
 -1.64680;-0.19869;1.16067;,
 -1.16413;-0.19836;1.11788;,
 1.19207;-4.87908;0.55081;,
 2.35174;-4.86352;0.52393;,
 -2.25683;-4.85751;0.72556;,
 0.07833;-4.87027;0.60980;,
 -1.30204;-4.87622;0.65933;,
 0.05764;-3.78233;-2.40088;,
 2.89899;-0.14913;-2.02539;,
 -2.91011;-4.02499;-2.04271;;
 
 137;
 3;0,1,2;,
 3;1,3,2;,
 3;3,4,2;,
 4;5,6,7,8;,
 4;9,10,11,12;,
 4;13,14,15,16;,
 4;17,18,19,20;,
 4;21,19,18,22;,
 4;23,24,25,26;,
 4;27,28,0,2;,
 4;29,30,31,32;,
 4;32,33,34,29;,
 4;35,36,37,38;,
 4;39,40,41,42;,
 4;43,44,45,46;,
 3;47,43,48;,
 3;43,49,48;,
 3;48,49,50;,
 3;49,51,50;,
 4;52,53,54,55;,
 4;56,54,53,57;,
 4;38,34,33,35;,
 3;1,5,3;,
 3;3,5,58;,
 3;5,8,58;,
 4;59,14,13,60;,
 4;61,62,63,64;,
 3;23,65,66;,
 3;65,67,66;,
 3;67,68,66;,
 4;69,24,23,66;,
 4;22,70,71,21;,
 4;57,72,73,56;,
 4;74,75,76,77;,
 4;78,75,74,79;,
 4;79,80,81,78;,
 4;82,81,80,83;,
 4;84,85,86,87;,
 3;85,88,86;,
 4;89,90,91,92;,
 4;93,90,89,94;,
 4;95,96,97,98;,
 4;99,100,101,102;,
 4;102,103,104,99;,
 4;76,104,103,77;,
 4;8,7,105,58;,
 3;21,106,19;,
 4;71,107,106,21;,
 4;108,105,109,2;,
 4;110,111,60,13;,
 3;109,105,112;,
 3;105,110,112;,
 3;110,13,112;,
 3;13,16,112;,
 3;19,106,20;,
 4;79,74,113,114;,
 4;32,31,113,115;,
 4;115,116,33,32;,
 4;35,33,116,117;,
 4;117,118,36,35;,
 4;42,41,119,120;,
 4;121,122,62,61;,
 4;46,45,123,124;,
 4;124,125,126,46;,
 3;127,128,129;,
 3;129,128,130;,
 3;128,131,130;,
 4;80,79,114,132;,
 4;26,25,16,15;,
 4;71,70,28,27;,
 4;30,73,72,31;,
 4;107,24,20,106;,
 3;133,72,57;,
 3;134,80,135;,
 3;135,80,136;,
 3;80,132,136;,
 4;137,27,2,109;,
 3;137,109,25;,
 3;109,112,25;,
 3;112,16,25;,
 4;25,24,138,139;,
 4;71,27,139,138;,
 4;104,140,141,99;,
 3;99,141,100;,
 3;81,142,78;,
 4;76,143,140,104;,
 4;91,88,85,92;,
 4;75,144,143,76;,
 4;75,78,142,144;,
 3;87,142,81;,
 3;142,87,144;,
 3;144,87,88;,
 3;87,86,88;,
 4;143,144,88,91;,
 4;140,143,91,90;,
 4;141,140,90,98;,
 4;100,141,98,97;,
 4;105,7,111,110;,
 4;11,10,7,6;,
 4;41,40,37,36;,
 4;118,119,41,36;,
 4;97,96,101,100;,
 4;115,113,74,77;,
 4;103,116,115,77;,
 4;117,116,103,102;,
 4;102,101,118,117;,
 4;96,119,118,101;,
 4;120,119,96,95;,
 4;94,89,122,121;,
 4;145,122,89,92;,
 4;85,127,145,92;,
 4;146,44,43,47;,
 4;64,63,14,59;,
 4;12,11,40,39;,
 4;37,40,11,6;,
 4;38,37,6,5;,
 4;5,1,34,38;,
 4;29,34,1,0;,
 4;28,30,29,0;,
 4;70,73,30,28;,
 4;56,73,70,22;,
 4;22,18,54,56;,
 4;55,54,18,17;,
 4;49,43,46,126;,
 3;129,130,67;,
 3;130,131,67;,
 3;131,68,67;,
 3;85,84,127;,
 3;127,84,147;,
 3;147,128,127;,
 3;133,114,72;,
 3;114,113,72;,
 3;113,31,72;,
 3;53,132,57;,
 3;132,114,57;,
 3;114,133,57;,
 4;136,132,53,52;;
 
 MeshMaterialList {
  1;
  137;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\dog_color.jpg";
   }
  }
 }
 MeshNormals {
  142;
  -0.550972;-0.351736;0.756777;,
  0.035873;-0.010021;0.999306;,
  0.611866;-0.373926;0.696993;,
  0.831679;-0.550784;0.070339;,
  0.541399;-0.517460;-0.662663;,
  -0.038231;-0.263943;-0.963780;,
  -0.544025;-0.751239;-0.373734;,
  -0.861797;-0.507254;-0.000664;,
  0.016202;0.999590;0.023597;,
  0.036161;0.993515;0.107797;,
  -0.000135;0.999990;0.004551;,
  -0.030528;0.999145;0.027871;,
  -0.045849;0.998895;0.010351;,
  -0.071729;0.997069;-0.026621;,
  -0.001462;0.999967;0.007945;,
  0.061148;0.998128;0.001521;,
  -0.060886;0.996910;0.049636;,
  -0.000312;0.999993;0.003734;,
  0.054354;0.996223;0.067718;,
  0.032563;0.998623;0.041131;,
  0.091801;0.995777;-0.000761;,
  -0.002779;0.999948;0.009816;,
  -0.143436;0.987914;-0.058761;,
  -0.091623;0.995686;0.014618;,
  0.162438;-0.058198;0.985001;,
  0.017514;0.999793;-0.010333;,
  0.019636;0.998567;0.049778;,
  0.023158;0.999521;0.020550;,
  0.058157;0.997411;0.042293;,
  0.039550;-0.309008;-0.950237;,
  -0.103999;-0.410492;-0.905914;,
  -0.077866;0.996569;-0.028062;,
  -0.039445;0.999158;-0.011292;,
  -0.002094;0.999985;0.004990;,
  -0.004039;0.999984;0.003914;,
  -0.112241;-0.094779;0.989151;,
  0.027513;-0.075619;0.996757;,
  -0.148127;-0.135427;0.979652;,
  -0.572242;-0.414530;0.707604;,
  -0.470347;-0.881873;0.032771;,
  -0.178759;-0.970652;-0.160873;,
  -0.065599;-0.860448;-0.505298;,
  -0.017548;-0.904184;-0.426782;,
  0.014640;-0.902598;-0.430235;,
  0.270379;-0.923450;-0.272279;,
  0.517774;-0.855370;0.015871;,
  0.533072;-0.713100;0.455326;,
  0.190642;-0.133234;0.972576;,
  -0.000143;0.999982;0.006071;,
  0.027058;0.999587;-0.009670;,
  -0.000145;0.999982;0.006070;,
  -0.000151;0.999982;0.006072;,
  -0.000899;0.999982;0.005950;,
  0.000136;0.999983;0.005885;,
  -0.648384;-0.040171;0.760253;,
  -0.053258;0.021774;0.998343;,
  0.046535;0.044034;0.997946;,
  0.149439;0.075157;0.985910;,
  0.620202;0.030349;0.783855;,
  0.984683;-0.081696;0.154032;,
  0.652773;0.082084;-0.753093;,
  0.106833;0.152470;-0.982517;,
  -0.021652;0.110923;-0.993593;,
  -0.335796;0.106191;-0.935930;,
  -0.668467;0.021961;-0.743418;,
  -0.990665;-0.047148;0.127908;,
  -0.120312;0.086390;0.988970;,
  -0.043804;0.999009;0.007917;,
  -0.004490;0.999979;0.004667;,
  -0.002097;0.999983;0.005525;,
  -0.021975;0.999734;0.006995;,
  -0.000607;0.999983;0.005760;,
  0.955591;0.095296;-0.278864;,
  -0.867665;-0.458667;-0.191785;,
  -0.163720;0.049510;0.985264;,
  -0.456977;0.073897;-0.886403;,
  -0.021445;-0.945892;-0.323772;,
  -0.066610;-0.997497;-0.023706;,
  -0.011067;-0.999557;-0.027624;,
  -0.002875;-0.999541;-0.030152;,
  0.005687;-0.999513;-0.030691;,
  0.107199;-0.993772;-0.030434;,
  -0.000142;0.999982;0.006067;,
  0.015310;0.999791;-0.013542;,
  0.030778;0.998976;-0.033167;,
  0.960730;-0.066783;-0.269328;,
  0.820309;-0.546652;-0.168122;,
  0.568908;-0.816444;-0.098811;,
  -0.077128;0.019399;0.996832;,
  0.045491;0.059582;0.997186;,
  0.132927;0.056426;0.989518;,
  0.618444;-0.153426;0.770705;,
  0.932655;-0.344438;0.107315;,
  0.918621;-0.331718;-0.214706;,
  0.905530;-0.305634;-0.294285;,
  0.058025;0.104017;-0.992881;,
  -0.035107;0.163649;-0.985894;,
  -0.195870;0.060677;-0.978751;,
  -0.018028;0.106303;-0.994170;,
  0.243098;0.154155;-0.957674;,
  0.711600;0.207588;-0.671217;,
  0.935201;0.175854;-0.307367;,
  0.973027;0.134271;0.187590;,
  0.601122;0.133808;0.787876;,
  0.192182;0.089725;0.977249;,
  0.056656;0.023472;0.998118;,
  -0.021789;0.008822;0.999724;,
  -0.246731;0.053439;0.967610;,
  -0.633680;0.104758;0.766469;,
  -0.977410;0.140992;0.157452;,
  -0.793553;0.216602;-0.568645;,
  -0.315683;0.122660;-0.940903;,
  -0.702454;-0.036066;-0.710814;,
  -0.523474;-0.182788;0.832204;,
  -0.937456;-0.286641;0.197515;,
  -0.027300;0.114004;-0.993105;,
  -0.041798;0.159980;-0.986235;,
  -0.439944;0.215742;-0.871725;,
  -0.833382;0.044705;-0.550887;,
  -0.813706;0.158500;-0.559250;,
  -0.883143;-0.104060;-0.457416;,
  0.158427;0.031843;-0.986857;,
  0.005135;-0.999360;-0.035409;,
  0.019512;-0.999230;-0.034040;,
  -0.070722;-0.997015;-0.030973;,
  -0.003030;-0.999303;-0.037202;,
  -0.015301;-0.999229;-0.036149;,
  0.337404;0.126991;-0.932755;,
  0.772446;0.164649;-0.613366;,
  0.926389;0.212206;-0.311081;,
  0.953926;0.223813;0.199833;,
  0.588280;0.208702;0.781262;,
  0.217493;0.125243;0.967993;,
  0.067170;0.022403;0.997490;,
  -0.014353;0.023580;0.999619;,
  -0.276065;0.096285;0.956304;,
  -0.652384;0.140369;0.744776;,
  -0.965771;0.194508;0.171620;,
  -0.253153;0.007040;-0.967401;,
  -0.298843;0.039916;-0.953467;,
  -0.186786;-0.033487;-0.981830;,
  0.832976;0.239601;-0.498740;;
  137;
  3;17,25,10;,
  3;25,49,10;,
  3;49,26,10;,
  4;18,19,8,9;,
  4;15,83,84,20;,
  4;27,28,21,14;,
  4;22,23,12,13;,
  4;11,12,23,16;,
  4;31,32,69,68;,
  4;33,34,17,10;,
  4;105,106,55,56;,
  4;56,57,104,105;,
  4;58,59,102,103;,
  4;100,101,85,60;,
  4;98,99,61,62;,
  3;115,98,116;,
  3;98,111,116;,
  3;116,111,117;,
  3;72,72,72;,
  4;64,65,109,110;,
  4;108,109,65,54;,
  4;103,104,57,58;,
  3;25,18,49;,
  3;49,18,26;,
  3;18,9,26;,
  4;20,28,27,15;,
  4;60,61,99,100;,
  3;117,118,119;,
  3;118,120,119;,
  3;111,110,119;,
  4;13,32,31,22;,
  4;16,67,70,11;,
  4;54,74,107,108;,
  4;35,37,36,1;,
  4;38,37,35,0;,
  4;0,7,39,38;,
  4;40,39,7,6;,
  4;6,30,41,40;,
  3;30,76,41;,
  4;29,43,42,5;,
  4;44,43,29,4;,
  4;4,86,87,44;,
  4;46,45,3,2;,
  4;2,24,47,46;,
  4;36,47,24,1;,
  4;9,8,50,26;,
  3;11,53,12;,
  4;70,71,53,11;,
  4;26,50,51,10;,
  4;82,83,15,27;,
  3;51,50,48;,
  3;50,82,48;,
  3;82,27,48;,
  3;27,14,48;,
  3;12,53,13;,
  4;0,35,88,113;,
  4;56,55,88,89;,
  4;89,90,57,56;,
  4;58,57,90,91;,
  4;91,92,59,58;,
  4;60,85,93,94;,
  4;121,95,61,60;,
  4;62,61,95,96;,
  4;96,97,63,62;,
  3;97,112,63;,
  3;63,112,75;,
  3;112,64,75;,
  4;7,0,113,114;,
  4;68,69,14,21;,
  4;70,67,34,33;,
  4;106,107,74,55;,
  4;71,32,13,53;,
  3;66,74,54;,
  3;6,7,73;,
  3;73,7,112;,
  3;7,114,112;,
  4;52,33,10,51;,
  3;52,51,69;,
  3;51,48,69;,
  3;48,14,69;,
  4;69,32,71,52;,
  4;70,33,52,71;,
  4;122,80,81,123;,
  3;46,81,45;,
  3;39,77,124;,
  4;125,79,80,122;,
  4;42,76,30,5;,
  4;126,78,79,125;,
  4;126,124,77,78;,
  3;40,77,39;,
  3;77,40,78;,
  3;78,40,76;,
  3;40,41,76;,
  4;79,78,76,42;,
  4;80,79,42,43;,
  4;81,80,43,44;,
  4;45,81,44,87;,
  4;50,8,83,82;,
  4;84,83,8,19;,
  4;85,101,102,59;,
  4;92,93,85,59;,
  4;87,86,3,45;,
  4;89,88,35,1;,
  4;24,90,89,1;,
  4;91,90,24,2;,
  4;2,3,92,91;,
  4;86,93,92,3;,
  4;94,93,86,4;,
  4;4,29,95,121;,
  4;96,95,29,5;,
  4;30,97,96,5;,
  4;127,99,98,115;,
  4;100,99,127,128;,
  4;128,129,101,100;,
  4;102,101,129,130;,
  4;103,102,130,131;,
  4;131,132,104,103;,
  4;105,104,132,133;,
  4;134,106,105,133;,
  4;135,107,106,134;,
  4;108,107,135,136;,
  4;136,137,109,108;,
  4;110,109,137,119;,
  4;111,98,62,63;,
  3;63,75,111;,
  3;75,64,111;,
  3;64,110,111;,
  3;30,138,97;,
  3;97,138,139;,
  3;139,112,97;,
  3;140,140,140;,
  3;113,88,74;,
  3;88,55,74;,
  3;65,114,54;,
  3;114,113,54;,
  3;141,141,141;,
  4;112,114,65,64;;
 }
 MeshTextureCoords {
  148;
  0.501705;0.224180;,
  0.517945;0.224180;,
  0.501705;0.220192;,
  0.517945;0.221481;,
  0.517945;0.220192;,
  0.538025;0.224180;,
  0.577148;0.224180;,
  0.577148;0.220192;,
  0.538025;0.220192;,
  0.614075;0.220192;,
  0.598626;0.220192;,
  0.598626;0.224180;,
  0.614075;0.224180;,
  0.517945;0.056215;,
  0.517945;0.095033;,
  0.501705;0.095033;,
  0.501705;0.056215;,
  0.385925;0.224180;,
  0.422852;0.224180;,
  0.422852;0.220192;,
  0.385925;0.220192;,
  0.461975;0.220192;,
  0.461975;0.224180;,
  0.479534;0.095033;,
  0.479534;0.056215;,
  0.480736;0.056215;,
  0.487369;0.095033;,
  0.479534;0.220192;,
  0.479534;0.224180;,
  0.501705;0.226241;,
  0.479534;0.226241;,
  0.479534;0.227633;,
  0.501705;0.227633;,
  0.517945;0.227633;,
  0.517945;0.226241;,
  0.538025;0.227633;,
  0.577148;0.227633;,
  0.577148;0.226241;,
  0.538025;0.226241;,
  0.614075;0.226241;,
  0.598626;0.226241;,
  0.598626;0.227633;,
  0.614075;0.227633;,
  0.815806;0.477763;,
  0.837903;0.477763;,
  0.837903;0.475868;,
  0.815806;0.475868;,
  0.815806;0.480567;,
  0.796299;0.480567;,
  0.785638;0.477719;,
  0.785638;0.480567;,
  0.785638;0.478358;,
  0.385925;0.227633;,
  0.422852;0.227633;,
  0.422852;0.226241;,
  0.385925;0.226241;,
  0.461975;0.226241;,
  0.461975;0.227633;,
  0.519943;0.220192;,
  0.538025;0.052227;,
  0.538025;0.056215;,
  0.538025;0.048774;,
  0.517945;0.091579;,
  0.517945;0.092972;,
  0.538025;0.050167;,
  0.479534;0.093409;,
  0.461975;0.052227;,
  0.479534;0.092939;,
  0.461975;0.050167;,
  0.461975;0.056215;,
  0.478048;0.224180;,
  0.470951;0.220192;,
  0.466769;0.227633;,
  0.471318;0.226241;,
  0.479534;0.230702;,
  0.479534;0.235180;,
  0.501705;0.235180;,
  0.501705;0.230702;,
  0.461975;0.235180;,
  0.461975;0.230702;,
  0.422852;0.230702;,
  0.422852;0.235180;,
  0.385925;0.235180;,
  0.386594;0.230702;,
  0.461975;0.045705;,
  0.479534;0.045705;,
  0.479534;0.041227;,
  0.461975;0.041227;,
  0.484495;0.041227;,
  0.517945;0.045705;,
  0.517945;0.041227;,
  0.501705;0.041227;,
  0.501705;0.045705;,
  0.538025;0.041227;,
  0.538025;0.045705;,
  0.614075;0.230702;,
  0.598626;0.230702;,
  0.598626;0.235180;,
  0.614075;0.235180;,
  0.538025;0.235180;,
  0.577148;0.235180;,
  0.577148;0.230702;,
  0.538025;0.230702;,
  0.517945;0.230702;,
  0.517945;0.235180;,
  0.519387;0.174606;,
  0.444356;0.220192;,
  0.464909;0.192801;,
  0.518944;0.220192;,
  0.505919;0.174039;,
  0.518549;0.105747;,
  0.554393;0.124819;,
  0.513005;0.096423;,
  0.479534;0.229879;,
  0.461975;0.229694;,
  0.501705;0.229879;,
  0.517945;0.229879;,
  0.538025;0.229879;,
  0.577148;0.229879;,
  0.598626;0.229879;,
  0.614075;0.229879;,
  0.538025;0.046528;,
  0.517945;0.089334;,
  0.837903;0.472812;,
  0.815806;0.472812;,
  0.785638;0.472812;,
  0.785638;0.475868;,
  0.479534;0.089334;,
  0.461975;0.046993;,
  0.479534;0.091579;,
  0.471887;0.048774;,
  0.461975;0.048774;,
  0.422852;0.229604;,
  0.461975;0.229172;,
  0.387262;0.230702;,
  0.385925;0.230580;,
  0.385925;0.229414;,
  0.479891;0.174557;,
  0.466588;0.190565;,
  0.479235;0.174570;,
  0.517945;0.149002;,
  0.571658;0.235180;,
  0.461975;0.149352;,
  0.501705;0.150133;,
  0.481728;0.149398;,
  0.501705;0.089334;,
  0.837903;0.480567;,
  0.461975;0.045827;;
 }
}
