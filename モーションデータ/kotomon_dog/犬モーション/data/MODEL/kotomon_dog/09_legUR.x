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
 126;
 -1.72661;-11.08782;0.59813;,
 -2.31325;-9.28707;-0.46533;,
 -2.72133;-9.73043;-1.47858;,
 -2.17272;-11.47565;-0.35584;,
 0.74824;-14.16215;1.40969;,
 -0.22395;-14.11363;1.98416;,
 -0.57542;-14.03661;1.08344;,
 0.25945;-14.07830;0.59011;,
 -0.01273;-9.62004;-2.29940;,
 0.52002;-11.42078;-1.20888;,
 -0.00704;-11.74929;-1.99812;,
 -0.55569;-10.00410;-3.12085;,
 -1.52307;-0.15502;-0.31064;,
 0.02758;-0.22526;-1.20965;,
 -1.23559;-1.31166;-2.73827;,
 -2.29498;-1.25874;-2.11227;,
 -1.70086;-12.17513;-1.01363;,
 -2.34744;-10.16127;-2.33836;,
 -1.38201;-10.28438;-3.07867;,
 -0.66965;-12.22659;-1.62295;,
 -2.39320;-6.92238;-0.73384;,
 -2.92035;-7.30096;-2.03977;,
 -3.05546;-7.64131;-3.41258;,
 -1.74698;-7.70664;-4.18580;,
 -0.12465;-7.32712;-2.71208;,
 -0.72990;-7.63298;-3.82462;,
 0.05010;-7.55404;-0.08776;,
 -0.12611;-6.75055;-0.41211;,
 -1.15730;-6.69904;0.19727;,
 -0.98108;-7.50254;0.52161;,
 1.14396;-13.15202;0.07939;,
 0.54465;-13.09909;-0.86035;,
 0.01173;-13.89382;-0.21758;,
 -1.01946;-13.84233;0.39177;,
 -1.62105;-12.82542;0.78195;,
 -1.15657;-12.81908;1.91345;,
 -2.54617;-5.15495;-0.72596;,
 -3.14295;-5.47259;-2.19326;,
 -3.07540;-5.40942;-3.46847;,
 -1.76685;-5.47477;-4.24168;,
 -0.32622;-5.58584;-2.73917;,
 -0.84700;-5.82931;-4.08354;,
 -0.04973;-4.81015;-0.61310;,
 -1.46316;-4.73958;0.22211;,
 -2.24349;-2.46927;-0.38415;,
 -2.98001;-3.45216;-2.11448;,
 -3.05224;-2.81375;-3.36527;,
 -1.74371;-2.87909;-4.13853;,
 -0.21024;-3.03828;-2.54976;,
 0.14686;-3.50553;-2.05749;,
 0.28882;-2.90149;0.20113;,
 -0.72492;-2.83584;1.52381;,
 -0.75241;-13.11554;2.56119;,
 -0.67306;-13.58720;1.83544;,
 -1.53520;-0.87766;0.76908;,
 -2.29353;-1.03852;-0.78134;,
 -1.56167;-3.55232;0.95917;,
 -1.90491;-4.82951;0.56661;,
 -1.72835;-6.65530;0.63563;,
 -1.63808;-7.40873;0.79749;,
 0.21915;-1.20560;-1.72118;,
 -0.06772;-1.35995;-1.92269;,
 -0.21024;-3.03828;-2.54976;,
 -0.84700;-5.82931;-4.08354;,
 -0.72990;-7.63298;-3.82462;,
 -0.55569;-10.00410;-3.12085;,
 -0.00704;-11.74929;-1.99812;,
 0.54465;-13.09909;-0.86035;,
 1.41332;-13.38924;0.91881;,
 0.85722;-13.78060;0.67497;,
 0.60772;-6.72921;-0.81014;,
 0.71270;-7.48091;-0.47639;,
 0.53706;-5.64259;-0.93742;,
 0.68245;-3.37031;-0.51737;,
 -1.00614;-1.01905;1.94181;,
 -0.64240;-0.25527;1.52602;,
 0.90829;-0.32553;0.62696;,
 0.53636;-1.90469;-0.74065;,
 0.66752;-3.11208;-1.04119;,
 0.36967;-5.58796;-1.17765;,
 0.53351;-6.68859;-1.19323;,
 0.67753;-8.05574;-0.87896;,
 1.06252;-9.57977;-0.09266;,
 1.51613;-11.49838;0.85290;,
 1.48335;-12.16103;1.08236;,
 0.48849;-13.15563;1.01611;,
 -0.06182;-12.71869;2.33503;,
 -0.77810;-11.99157;2.53418;,
 -1.03520;-11.23414;2.65565;,
 -1.63267;-9.47218;1.42359;,
 -1.85887;-7.77527;0.95349;,
 -1.86781;-7.55166;0.95806;,
 -1.93398;-5.16185;0.87168;,
 -1.99686;-2.73069;0.40796;,
 -0.48078;-1.35922;1.71052;,
 -0.62485;-0.98903;1.77028;,
 0.60423;-1.38419;1.13550;,
 0.78273;-1.93236;-0.17849;,
 0.53706;-5.64259;-0.93742;,
 0.68245;-3.37031;-0.51737;,
 0.60772;-6.72921;-0.81014;,
 0.71270;-7.48091;-0.47639;,
 -0.62485;-0.98903;1.77028;,
 -1.00614;-1.01905;1.94181;,
 -1.53520;-0.87766;0.76908;,
 -2.29353;-1.03852;-0.78134;,
 -2.29498;-1.25874;-2.11227;,
 -1.23559;-1.31166;-2.73827;,
 -0.06772;-1.35995;-1.92269;,
 0.78273;-1.93236;-0.17849;,
 0.60423;-1.38419;1.13550;,
 -0.48078;-1.35922;1.71052;,
 0.25945;-14.07830;0.59011;,
 0.85722;-13.78060;0.67497;,
 -0.57542;-14.03661;1.08344;,
 -1.22612;-9.18092;1.60680;,
 -0.63397;-9.23638;1.18555;,
 1.04627;-9.26415;0.17609;,
 1.08919;-9.52668;-0.03192;,
 0.37414;-9.25550;0.57637;,
 -0.80841;-11.26003;2.46559;,
 -0.27646;-11.41220;1.90372;,
 0.70934;-11.45074;1.31661;,
 1.38339;-11.49856;0.87513;,
 -0.16723;-12.07713;2.12323;,
 0.80977;-12.10832;1.53834;;
 
 104;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;1,20,21,2;,
 4;17,22,23,18;,
 4;24,8,11,25;,
 4;26,27,28,29;,
 4;9,30,31,10;,
 4;32,33,16,19;,
 4;34,35,0,3;,
 4;20,36,37,21;,
 4;22,38,39,23;,
 4;40,24,25,41;,
 4;27,42,43,28;,
 4;36,44,45,37;,
 4;38,46,47,39;,
 4;48,49,40,41;,
 4;42,50,51,43;,
 4;5,52,53,6;,
 4;3,16,33,34;,
 4;2,17,16,3;,
 4;21,22,17,2;,
 4;37,38,22,21;,
 4;45,46,38,37;,
 4;54,12,15,55;,
 4;43,51,56,57;,
 4;28,43,57,58;,
 4;29,28,58,59;,
 4;13,60,61,14;,
 4;39,47,62,63;,
 4;23,39,63,64;,
 4;18,23,64,65;,
 4;19,18,65,66;,
 4;67,32,19,66;,
 4;68,4,7,69;,
 4;70,27,26,71;,
 4;72,42,27,70;,
 4;73,50,42,72;,
 4;74,75,12,54;,
 4;75,76,13,12;,
 4;76,77,60,13;,
 4;49,78,79,40;,
 4;79,80,24,40;,
 4;80,81,8,24;,
 4;81,82,9,8;,
 4;82,83,30,9;,
 4;84,85,4,68;,
 4;85,86,5,4;,
 4;86,87,52,5;,
 4;35,88,89,0;,
 4;89,90,1,0;,
 4;90,91,20,1;,
 4;91,92,36,20;,
 4;92,93,44,36;,
 4;94,75,74,95;,
 4;96,76,75,94;,
 4;97,77,76,96;,
 4;98,79,78,99;,
 4;100,80,79,98;,
 4;101,81,80,100;,
 4;58,91,90,59;,
 4;57,92,91,58;,
 4;56,93,92,57;,
 4;102,103,93,56;,
 4;44,93,103,104;,
 4;45,44,104,105;,
 4;105,106,46,45;,
 4;47,46,106,107;,
 4;62,47,107,108;,
 4;60,49,48,61;,
 4;77,78,49,60;,
 4;99,78,77,97;,
 4;109,110,50,73;,
 4;51,50,110,111;,
 4;56,51,111,102;,
 4;30,83,84,68;,
 4;31,30,68,69;,
 4;112,32,67,113;,
 4;114,33,32,112;,
 4;34,33,114,53;,
 4;52,35,34,53;,
 4;87,88,35,52;,
 4;59,115,116,29;,
 4;90,89,115,59;,
 4;71,117,118,81;,
 4;29,116,119,26;,
 4;26,119,117,71;,
 3;81,118,82;,
 4;115,89,88,120;,
 4;116,115,120,121;,
 4;119,116,121,122;,
 4;117,119,122,123;,
 4;118,117,123,83;,
 3;82,118,83;,
 3;120,88,87;,
 3;124,87,86;,
 4;125,124,86,85;,
 3;84,125,85;,
 3;83,123,84;,
 4;123,122,125,84;,
 4;122,121,124,125;,
 4;121,120,87,124;;
 
 MeshMaterialList {
  1;
  104;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  131;
  0.599127;0.265752;0.755264;,
  -0.916726;0.343942;0.203268;,
  -0.774869;-0.564684;0.284095;,
  0.559698;-0.741136;-0.370751;,
  0.996084;-0.081593;0.034050;,
  0.600195;0.294356;-0.743721;,
  0.328181;0.315552;0.890350;,
  -0.975447;-0.169520;0.140592;,
  0.557066;-0.285074;-0.780007;,
  0.439895;0.402862;0.802617;,
  0.508830;-0.393692;-0.765571;,
  -0.959872;-0.247606;0.131667;,
  0.668081;0.159775;0.726732;,
  -0.978543;-0.088159;0.186230;,
  0.618599;-0.112575;-0.777600;,
  0.474538;0.261488;0.840498;,
  0.575428;-0.068779;0.814955;,
  -0.979864;-0.010711;0.199379;,
  0.691197;0.052419;-0.720763;,
  0.508951;-0.103530;0.854547;,
  -0.488257;-0.867863;0.091759;,
  -0.702963;-0.575783;-0.417512;,
  -0.780565;-0.446407;-0.437538;,
  -0.860872;-0.206263;-0.465139;,
  -0.508485;0.006338;-0.861048;,
  -0.657320;0.708992;-0.255461;,
  0.367326;0.009091;0.930048;,
  0.511441;-0.224364;0.829511;,
  0.532321;0.228549;0.815107;,
  0.486994;0.392497;0.780246;,
  0.687724;-0.136596;0.713006;,
  0.141394;0.659998;-0.737842;,
  -0.273766;-0.019804;-0.961592;,
  -0.158844;-0.229780;-0.960193;,
  -0.198817;-0.511112;-0.836203;,
  -0.206230;-0.643862;-0.736825;,
  0.219875;-0.943069;-0.249551;,
  0.459788;0.404861;0.790369;,
  0.488378;0.254216;0.834783;,
  0.533126;-0.168020;0.829184;,
  -0.867643;0.369308;0.332876;,
  -0.477024;0.878543;0.024718;,
  0.102090;0.884413;-0.455403;,
  0.798770;0.232488;-0.554902;,
  0.900176;0.019976;-0.435069;,
  0.899236;0.021319;-0.436944;,
  0.883122;-0.037718;-0.467624;,
  0.873588;-0.042665;-0.484792;,
  0.763303;-0.540605;-0.353715;,
  0.249652;-0.947407;-0.200234;,
  -0.471543;-0.873657;0.119880;,
  -0.791734;-0.440403;0.423323;,
  -0.929402;-0.053099;0.365229;,
  -0.935424;-0.030358;0.352222;,
  -0.937890;-0.035007;0.345163;,
  -0.934878;-0.003515;0.354952;,
  -0.840509;0.370878;0.394961;,
  -0.379616;0.894655;0.235551;,
  0.060083;0.997864;0.025660;,
  0.967399;0.087798;-0.237550;,
  0.921590;0.023846;-0.387431;,
  0.936202;0.064337;-0.345524;,
  0.945848;0.046084;-0.321323;,
  0.905322;0.007393;-0.424662;,
  0.351759;0.076933;0.932924;,
  0.548157;-0.085567;0.831987;,
  0.611448;0.069969;0.788185;,
  0.570942;0.138124;0.809288;,
  -0.651819;0.195837;0.732652;,
  -0.814272;0.076952;0.575361;,
  -0.950672;-0.035041;0.308211;,
  -0.943595;0.003069;0.331089;,
  -0.032870;-0.222794;0.974311;,
  -0.791795;-0.032778;0.609907;,
  -0.925098;0.086366;0.369777;,
  -0.968929;0.122217;0.215035;,
  -0.454829;0.386444;-0.802366;,
  0.705757;0.160948;-0.689929;,
  0.871963;0.032954;-0.488461;,
  0.943421;0.014455;-0.331281;,
  0.701733;-0.299619;0.646373;,
  0.637710;-0.367719;0.676838;,
  0.283596;-0.407543;0.868033;,
  0.928762;-0.018276;-0.370227;,
  0.875551;-0.219797;-0.430232;,
  0.696086;-0.545287;-0.467040;,
  -0.005394;-0.844943;-0.534830;,
  -0.618110;-0.765547;-0.178546;,
  -0.879577;-0.419182;0.225012;,
  -0.877280;-0.206674;0.433203;,
  -0.856609;-0.129956;0.499332;,
  0.233827;0.433900;0.870090;,
  0.526652;0.385194;0.757802;,
  0.484202;0.366347;0.794568;,
  0.928278;0.292286;0.229931;,
  0.981125;0.157287;-0.112497;,
  0.517942;0.315334;0.795173;,
  0.574012;0.321375;0.753146;,
  0.507530;0.339485;0.791936;,
  0.498070;0.349996;0.793366;,
  0.586017;0.028383;0.809802;,
  0.611117;0.213734;0.762137;,
  -0.999851;-0.010941;0.013357;,
  -0.984127;0.172322;0.042428;,
  0.536226;0.222770;-0.814147;,
  0.585511;0.260490;-0.767673;,
  0.024348;-0.638477;-0.769255;,
  0.977396;0.090459;-0.191089;,
  0.938103;0.206549;-0.278029;,
  0.467733;0.135498;0.873422;,
  0.138028;0.137936;0.980776;,
  0.575051;-0.001848;0.818115;,
  0.370750;-0.120343;0.920903;,
  0.540022;0.250931;0.803374;,
  0.477663;0.234598;0.846642;,
  0.994619;-0.027674;-0.099834;,
  0.934219;0.027830;-0.355612;,
  0.959263;0.018925;-0.281880;,
  0.957821;0.074999;-0.277404;,
  0.979663;0.111713;-0.166672;,
  0.765916;0.103755;0.634514;,
  0.515742;0.123497;0.847796;,
  0.669271;0.088035;0.737784;,
  0.259421;0.084092;0.962096;,
  -0.328581;-0.211582;0.920471;,
  -0.271455;-0.295741;0.915887;,
  0.963336;-0.066974;-0.259804;,
  -0.728669;-0.165277;0.664624;,
  0.482573;0.361998;0.797547;,
  0.356841;0.327688;0.874806;,
  0.469278;0.366530;0.803389;;
  104;
  4;52,53,7,11;,
  4;49,50,20,36;,
  4;46,47,10,8;,
  4;41,42,31,25;,
  4;21,22,34,35;,
  4;53,54,13,7;,
  4;22,23,33,34;,
  4;45,46,8,14;,
  4;37,38,28,29;,
  4;47,84,85,10;,
  4;86,87,21,35;,
  4;88,89,52,11;,
  4;54,55,17,13;,
  4;23,24,32,33;,
  4;44,45,14,18;,
  4;38,39,27,28;,
  4;55,74,75,17;,
  4;24,76,76,32;,
  4;77,78,44,18;,
  4;39,81,82,27;,
  4;50,51,2,20;,
  4;11,21,87,88;,
  4;7,22,21,11;,
  4;13,23,22,7;,
  4;17,102,23,13;,
  4;75,103,102,17;,
  4;40,41,25,1;,
  4;27,82,72,16;,
  4;28,27,16,12;,
  4;29,28,12,6;,
  4;42,43,5,31;,
  4;104,105,77,18;,
  4;33,32,18,14;,
  4;34,33,14,8;,
  4;35,34,8,10;,
  4;106,86,35,10;,
  4;48,49,36,3;,
  4;15,38,37,9;,
  4;19,39,38,15;,
  4;80,81,39,19;,
  4;56,57,41,40;,
  4;57,58,42,41;,
  4;107,59,43,108;,
  4;78,79,60,44;,
  4;60,61,45,44;,
  4;61,62,46,45;,
  4;62,63,47,46;,
  4;63,83,84,47;,
  4;64,65,109,110;,
  4;65,66,111,109;,
  4;66,67,112,111;,
  4;89,90,68,52;,
  4;68,69,53,52;,
  4;69,70,54,53;,
  4;70,71,55,54;,
  4;71,73,74,55;,
  4;26,113,0,0;,
  4;30,114,113,26;,
  4;4,59,107,115;,
  4;116,60,79,117;,
  4;118,61,60,116;,
  4;119,62,61,118;,
  4;12,120,121,6;,
  4;16,122,120,12;,
  4;72,123,122,16;,
  4;124,125,73,72;,
  4;74,73,56,40;,
  4;75,74,40,1;,
  4;1,25,103,75;,
  4;76,76,25,31;,
  4;77,105,31,5;,
  4;43,78,77,5;,
  4;59,79,78,43;,
  4;117,79,59,4;,
  4;4,30,81,80;,
  4;82,81,30,26;,
  4;72,82,26,124;,
  4;84,83,126,48;,
  4;85,84,48,3;,
  4;36,86,85,3;,
  4;20,87,86,36;,
  4;88,87,20,2;,
  4;51,89,88,2;,
  4;127,90,89,51;,
  4;6,91,92,29;,
  4;69,68,91,6;,
  4;119,94,95,62;,
  4;29,92,93,37;,
  4;37,93,128,9;,
  3;62,95,63;,
  4;91,68,129,96;,
  4;92,91,96,97;,
  4;93,92,97,98;,
  4;128,93,98,99;,
  4;95,94,99,130;,
  3;63,95,83;,
  3;96,129,67;,
  3;101,67,66;,
  4;100,101,66,65;,
  3;64,100,65;,
  3;130,99,64;,
  4;99,98,100,64;,
  4;98,97,101,100;,
  4;97,96,67,101;;
 }
 MeshTextureCoords {
  126;
  0.506283;0.210835;,
  0.506283;0.216966;,
  0.518280;0.216966;,
  0.518280;0.210835;,
  0.506283;0.175001;,
  0.506283;0.191645;,
  0.518280;0.191645;,
  0.518280;0.175001;,
  0.506283;0.145193;,
  0.506283;0.151324;,
  0.518280;0.151324;,
  0.518280;0.145193;,
  0.506283;0.097393;,
  0.506283;0.114037;,
  0.518280;0.114037;,
  0.518280;0.097393;,
  0.525996;0.210835;,
  0.525996;0.216966;,
  0.542640;0.216966;,
  0.542640;0.210835;,
  0.506283;0.221299;,
  0.518280;0.221299;,
  0.525996;0.221299;,
  0.542640;0.221299;,
  0.506283;0.140860;,
  0.518280;0.140860;,
  0.457360;0.216966;,
  0.457360;0.221299;,
  0.474004;0.221299;,
  0.474004;0.216966;,
  0.506283;0.157724;,
  0.518280;0.157724;,
  0.542640;0.204436;,
  0.525996;0.204436;,
  0.518280;0.204436;,
  0.506283;0.204436;,
  0.506283;0.223715;,
  0.518280;0.223715;,
  0.525996;0.223715;,
  0.542640;0.223715;,
  0.506283;0.138444;,
  0.518280;0.138444;,
  0.457360;0.223715;,
  0.474004;0.223715;,
  0.506283;0.229809;,
  0.518280;0.229809;,
  0.525996;0.229809;,
  0.542640;0.229809;,
  0.518280;0.132350;,
  0.506283;0.132350;,
  0.457360;0.229809;,
  0.474004;0.229809;,
  0.506283;0.199360;,
  0.518280;0.199360;,
  0.506283;0.089678;,
  0.518280;0.089678;,
  0.481720;0.229809;,
  0.481720;0.223715;,
  0.481720;0.221299;,
  0.481720;0.216966;,
  0.506283;0.126238;,
  0.518280;0.126238;,
  0.554841;0.229809;,
  0.554841;0.223715;,
  0.554841;0.221299;,
  0.554841;0.216966;,
  0.554841;0.210835;,
  0.554841;0.204436;,
  0.506283;0.162799;,
  0.518280;0.162799;,
  0.445159;0.221299;,
  0.445159;0.216966;,
  0.445159;0.223715;,
  0.445159;0.229809;,
  0.490703;0.089678;,
  0.490703;0.097393;,
  0.490703;0.114037;,
  0.490703;0.126238;,
  0.490703;0.132350;,
  0.490703;0.138444;,
  0.490703;0.140860;,
  0.490703;0.145193;,
  0.490703;0.151324;,
  0.490703;0.157724;,
  0.490703;0.162799;,
  0.490703;0.175001;,
  0.490703;0.191645;,
  0.490703;0.199360;,
  0.490703;0.204436;,
  0.490703;0.210835;,
  0.490703;0.216966;,
  0.490703;0.221299;,
  0.490703;0.223715;,
  0.490703;0.229809;,
  0.481720;0.097393;,
  0.481720;0.089678;,
  0.481720;0.114037;,
  0.481720;0.126238;,
  0.481720;0.138444;,
  0.481720;0.132350;,
  0.481720;0.140860;,
  0.481720;0.145193;,
  0.481720;0.235921;,
  0.490703;0.235921;,
  0.506283;0.235921;,
  0.518280;0.235921;,
  0.525996;0.235921;,
  0.542640;0.235921;,
  0.554841;0.235921;,
  0.445159;0.235921;,
  0.457360;0.235921;,
  0.474004;0.235921;,
  0.542640;0.199360;,
  0.554841;0.199360;,
  0.525996;0.199360;,
  0.485057;0.210426;,
  0.479173;0.209128;,
  0.461433;0.197611;,
  0.490703;0.150714;,
  0.467473;0.204238;,
  0.489394;0.201925;,
  0.486377;0.198204;,
  0.481995;0.185961;,
  0.484009;0.170760;,
  0.488579;0.194866;,
  0.486344;0.180486;;
 }
}
