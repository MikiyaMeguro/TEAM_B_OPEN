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
 243;
 -7.48235;1.07596;0.38415;,
 -6.18103;1.32293;0.42545;,
 -6.19516;1.34248;-0.67283;,
 -7.49395;1.09205;-0.51816;,
 -8.08837;-0.30170;-0.33217;,
 -8.08262;-0.38497;0.07240;,
 -8.08568;0.03348;0.07989;,
 -8.09186;0.04209;-0.40206;,
 -5.97023;-1.19148;-0.52705;,
 -6.16694;-1.18492;0.03312;,
 -7.47106;-0.95624;0.05393;,
 -7.47890;-0.94538;-0.55467;,
 -0.28293;-0.69769;-0.03170;,
 -0.40619;-0.64585;-0.87387;,
 -0.29988;0.08364;-0.89980;,
 -0.28855;0.06791;-0.01799;,
 -7.49139;0.04176;-0.94504;,
 -5.69601;0.05019;-1.20567;,
 -6.06351;-0.42298;-1.20953;,
 -7.48747;-0.48665;-0.95452;,
 -7.46128;-0.52298;1.08280;,
 -6.15490;-0.65030;1.30267;,
 -6.15969;0.00171;1.31435;,
 -7.46519;0.00542;1.09227;,
 -3.25406;1.54229;-0.81160;,
 -3.24307;1.52705;0.04464;,
 -2.42418;1.41711;0.03271;,
 -2.43427;1.43115;-0.75427;,
 -2.14860;-0.42239;-1.31859;,
 -3.22281;-0.67857;-1.42576;,
 -3.59130;0.06218;-1.40795;,
 -2.21129;0.27758;-1.30533;,
 -2.40472;-1.21738;-0.01451;,
 -3.22189;-1.33932;-0.00673;,
 -3.23291;-1.32406;-0.86296;,
 -2.41484;-1.20336;-0.80149;,
 -3.20817;-0.72980;1.44073;,
 -2.39205;-0.65719;1.31589;,
 -2.39712;0.02611;1.32814;,
 -3.21358;0.01358;1.45405;,
 -2.42418;1.41711;0.03271;,
 -0.67914;1.45554;0.01159;,
 -0.87731;1.40390;-0.72601;,
 -2.43427;1.43115;-0.75427;,
 -2.21129;0.27758;-1.30533;,
 -0.68601;0.08545;-1.35331;,
 -0.85098;-0.55623;-1.30555;,
 -2.14860;-0.42239;-1.31859;,
 -0.65927;-1.23004;-0.03656;,
 -2.40472;-1.21738;-0.01451;,
 -2.41484;-1.20336;-0.80149;,
 -0.85842;-1.15486;-0.77187;,
 -2.39205;-0.65719;1.31589;,
 -0.81795;-0.60208;1.26564;,
 -0.65154;0.03757;1.33211;,
 -2.39712;0.02611;1.32814;,
 -7.80462;-0.67392;0.06374;,
 -7.80957;-0.54013;-0.24420;,
 -7.81925;0.04510;-0.65598;,
 -7.81586;-0.22214;-0.54520;,
 -7.81547;0.79396;0.09004;,
 -7.81851;0.67122;-0.22249;,
 -7.79997;-0.24418;0.69153;,
 -7.80042;0.01894;0.81181;,
 -0.27723;0.05222;0.86332;,
 -0.38398;-0.67614;0.81423;,
 -0.83854;-1.18147;0.70558;,
 -2.39461;-1.23141;0.77204;,
 -2.39461;-1.23141;0.77204;,
 -3.21089;-1.35459;0.84904;,
 -3.22189;-1.33932;-0.00673;,
 -2.40472;-1.21738;-0.01451;,
 -5.95591;-1.21135;0.58704;,
 -7.46327;-0.96707;0.66224;,
 -7.80160;-0.55180;0.37660;,
 -8.07792;-0.31655;0.47981;,
 -8.07950;0.02490;0.56160;,
 -7.81052;0.66075;0.39835;,
 -7.47830;1.07035;0.69875;,
 -7.48235;1.07596;0.38415;,
 -7.81547;0.79396;0.09004;,
 -6.17587;1.31573;0.82876;,
 -6.18103;1.32293;0.42545;,
 -3.24307;1.52705;0.04464;,
 -3.23206;1.51177;0.90041;,
 -2.41407;1.40308;0.81925;,
 -2.42418;1.41711;0.03271;,
 -2.41407;1.40308;0.81925;,
 -0.85745;1.37787;0.75145;,
 -8.08262;0.33839;0.50434;,
 -8.08843;0.40871;0.08663;,
 -8.09339;0.35306;-0.33330;,
 -7.81983;0.28879;-0.55561;,
 -7.49665;0.51806;-1.07483;,
 -6.19806;0.63374;-1.32735;,
 -3.25538;0.73134;-1.40020;,
 -1.91010;0.72226;-1.30117;,
 -1.91010;0.72226;-1.30117;,
 -0.83126;0.66069;-1.29375;,
 -0.39752;0.73772;-0.85567;,
 -0.29365;0.75448;-0.00568;,
 -0.37518;0.70755;0.84511;,
 -0.79797;0.61452;1.29674;,
 -2.40165;0.63883;1.33912;,
 -2.40165;0.63883;1.33912;,
 -3.52083;0.67802;1.46973;,
 -5.82098;0.58895;1.32060;,
 -7.46873;0.47929;1.10077;,
 -7.80344;0.26603;0.72022;,
 -0.65154;0.03757;1.33211;,
 -0.79797;0.61452;1.29674;,
 -0.81795;-0.60208;1.26564;,
 -2.66932;-1.03126;1.09551;,
 -1.21500;-1.06088;1.11273;,
 -3.40100;-1.03780;1.20137;,
 -2.66932;-1.03126;1.09551;,
 -7.48152;-0.81202;0.90878;,
 -5.76464;-1.00311;1.08362;,
 -7.79949;-0.46898;0.58878;,
 -7.80042;0.01894;0.81181;,
 -7.79997;-0.24418;0.69153;,
 -7.80344;0.26603;0.72022;,
 -7.46074;0.89706;0.93899;,
 -7.80720;0.57045;0.60739;,
 -6.07461;1.19366;1.21874;,
 -2.68560;1.17835;1.13511;,
 -3.39363;1.26822;1.24240;,
 -1.23187;1.22430;1.15368;,
 -2.68560;1.17835;1.13511;,
 -3.34234;-1.09252;-1.20540;,
 -2.52998;-1.10069;-1.23011;,
 -2.52998;-1.10069;-1.23011;,
 -1.24434;-1.02013;-1.17232;,
 -0.68601;0.08545;-1.35331;,
 -0.29988;0.08364;-0.89980;,
 -0.40619;-0.64585;-0.87387;,
 -0.85098;-0.55623;-1.30555;,
 -0.83126;0.66069;-1.29375;,
 -0.39752;0.73772;-0.85567;,
 -1.26121;1.26503;-1.13136;,
 -2.71400;1.21772;-1.07439;,
 -3.42446;1.31105;-1.16153;,
 -2.71400;1.21772;-1.07439;,
 -5.98959;1.36001;-1.22876;,
 -7.01278;1.22333;-1.09651;,
 -7.82372;0.74548;-0.58943;,
 -7.81925;0.04510;-0.65598;,
 -7.81983;0.28879;-0.55561;,
 -7.81586;-0.22214;-0.54520;,
 -7.81288;-0.45046;-0.45058;,
 -7.43142;-0.78510;-0.57308;,
 -5.71148;-0.96491;-1.02581;,
 -4.57375;1.22934;1.22568;,
 -4.59682;1.46531;0.89472;,
 -5.01967;1.47715;0.06599;,
 -5.01967;1.47715;0.06599;,
 -4.76924;1.49396;-0.77152;,
 -4.74624;1.27004;-1.11480;,
 -5.06789;0.70159;-1.34136;,
 -4.61470;0.05538;-1.35853;,
 -4.60934;-0.66898;-1.37152;,
 -6.06351;-0.42298;-1.20953;,
 -5.69601;0.05019;-1.20567;,
 -4.61470;0.05538;-1.35853;,
 -4.79872;-1.28514;-0.60537;,
 -5.97023;-1.19148;-0.52705;,
 -5.71148;-0.96491;-1.02581;,
 -4.58652;-1.07128;-1.15854;,
 -4.58692;-1.31265;0.01086;,
 -6.16694;-1.18492;0.03312;,
 -5.97023;-1.19148;-0.52705;,
 -4.79872;-1.28514;-0.60537;,
 -4.78282;-1.30720;0.63226;,
 -5.95591;-1.21135;0.58704;,
 -4.78282;-1.30720;0.63226;,
 -4.55644;-1.11304;1.18370;,
 -6.15490;-0.65030;1.30267;,
 -4.57347;-0.71877;1.42117;,
 -4.59615;0.01268;1.30587;,
 -6.15969;0.00171;1.31435;,
 -4.58361;0.65514;1.44580;,
 -5.82098;0.58895;1.32060;,
 -4.61470;0.05538;-1.35853;,
 -3.59130;0.06218;-1.40795;,
 -3.22281;-0.67857;-1.42576;,
 -4.60934;-0.66898;-1.37152;,
 -3.25538;0.73134;-1.40020;,
 -3.59130;0.06218;-1.40795;,
 -4.76924;1.49396;-0.77152;,
 -3.25406;1.54229;-0.81160;,
 -3.42446;1.31105;-1.16153;,
 -4.74624;1.27004;-1.11480;,
 -3.21358;0.01358;1.45405;,
 -3.52083;0.67802;1.46973;,
 -4.57347;-0.71877;1.42117;,
 -3.20817;-0.72980;1.44073;,
 -3.21358;0.01358;1.45405;,
 -4.59615;0.01268;1.30587;,
 -4.58692;-1.31265;0.01086;,
 -3.23291;-1.32406;-0.86296;,
 -4.79872;-1.28514;-0.60537;,
 -3.34234;-1.09252;-1.20540;,
 -3.23291;-1.32406;-0.86296;,
 -7.81851;0.67122;-0.22249;,
 -7.82372;0.74548;-0.58943;,
 -7.49665;0.51806;-1.07483;,
 -7.81983;0.28879;-0.55561;,
 -6.19806;0.63374;-1.32735;,
 -5.06789;0.70159;-1.34136;,
 -0.83126;0.66069;-1.29375;,
 -1.91010;0.72226;-1.30117;,
 -0.87731;1.40390;-0.72601;,
 -0.83126;0.66069;-1.29375;,
 -1.26121;1.26503;-1.13136;,
 -0.67914;1.45554;0.01159;,
 -0.85745;1.37787;0.75145;,
 -1.23187;1.22430;1.15368;,
 -4.58361;0.65514;1.44580;,
 -0.85098;-0.55623;-1.30555;,
 -2.14860;-0.42239;-1.31859;,
 -0.85098;-0.55623;-1.30555;,
 -1.24434;-1.02013;-1.17232;,
 -2.52998;-1.10069;-1.23011;,
 -3.34234;-1.09252;-1.20540;,
 -2.52998;-1.10069;-1.23011;,
 -3.22281;-0.67857;-1.42576;,
 -3.34234;-1.09252;-1.20540;,
 -4.58652;-1.07128;-1.15854;,
 -5.71148;-0.96491;-1.02581;,
 -5.71148;-0.96491;-1.02581;,
 -7.43142;-0.78510;-0.57308;,
 -7.81288;-0.45046;-0.45058;,
 -7.48152;-0.81202;0.90878;,
 -7.79949;-0.46898;0.58878;,
 -5.76464;-1.00311;1.08362;,
 -4.55644;-1.11304;1.18370;,
 -5.76464;-1.00311;1.08362;,
 -3.40100;-1.03780;1.20137;,
 -3.20817;-0.72980;1.44073;,
 -2.66932;-1.03126;1.09551;,
 -3.40100;-1.03780;1.20137;,
 -1.21500;-1.06088;1.11273;,
 -2.66932;-1.03126;1.09551;;
 
 128;
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
 4;10,56,57,11;,
 4;58,16,19,59;,
 4;60,0,3,61;,
 4;62,20,23,63;,
 4;64,65,12,15;,
 4;66,67,49,48;,
 4;68,69,70,71;,
 4;9,72,73,10;,
 4;73,74,56,10;,
 4;5,75,76,6;,
 4;77,78,79,80;,
 4;78,81,82,79;,
 4;83,84,85,86;,
 4;87,88,41,40;,
 4;76,89,90,6;,
 4;90,91,7,6;,
 4;92,93,16,58;,
 4;93,94,17,16;,
 4;95,96,31,30;,
 4;97,98,45,44;,
 4;99,100,15,14;,
 4;100,101,64,15;,
 4;55,54,102,103;,
 4;104,105,39,38;,
 4;23,22,106,107;,
 4;63,23,107,108;,
 4;109,64,101,110;,
 4;111,65,64,109;,
 4;112,67,66,113;,
 4;114,69,68,115;,
 4;116,73,72,117;,
 4;118,74,73,116;,
 4;119,76,75,120;,
 4;121,89,76,119;,
 4;122,78,77,123;,
 4;124,81,78,122;,
 4;125,85,84,126;,
 4;127,88,87,128;,
 4;35,34,129,130;,
 4;51,50,131,132;,
 4;133,134,135,136;,
 4;137,138,134,133;,
 4;43,42,139,140;,
 4;141,24,27,142;,
 4;3,2,143,144;,
 4;61,3,144,145;,
 4;146,7,91,147;,
 4;148,4,7,146;,
 4;11,57,149,150;,
 4;151,8,11,150;,
 4;152,153,81,124;,
 4;82,81,153,154;,
 4;2,1,155,156;,
 4;143,2,156,157;,
 4;94,158,159,17;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,169,168;,
 4;117,72,174,175;,
 4;176,177,178,179;,
 4;180,181,179,178;,
 4;182,183,184,185;,
 4;158,186,187,159;,
 4;188,189,190,191;,
 4;154,83,189,188;,
 4;153,84,83,154;,
 4;126,84,153,152;,
 4;178,192,193,180;,
 4;194,195,196,197;,
 4;175,174,69,114;,
 4;70,69,174,198;,
 4;199,70,198,200;,
 4;201,202,164,167;,
 4;123,77,89,121;,
 4;90,89,77,80;,
 4;203,91,90,80;,
 4;147,91,203,204;,
 4;144,205,206,145;,
 4;143,207,205,144;,
 4;157,208,207,143;,
 4;190,186,158,191;,
 4;142,96,95,141;,
 4;139,209,210,140;,
 4;211,99,212,213;,
 4;214,100,99,211;,
 4;215,101,100,214;,
 4;110,101,215,216;,
 4;103,102,127,128;,
 4;126,105,104,125;,
 4;217,105,126,152;,
 4;124,106,217,152;,
 4;107,106,124,122;,
 4;108,107,122,123;,
 4;113,66,65,111;,
 4;12,65,66,48;,
 4;51,13,12,48;,
 4;218,13,51,132;,
 4;219,220,221,222;,
 4;223,29,28,224;,
 4;160,225,226,227;,
 4;228,161,160,227;,
 4;19,18,229,230;,
 4;59,19,230,231;,
 4;57,4,148,149;,
 4;56,5,4,57;,
 4;74,75,5,56;,
 4;120,75,74,118;,
 4;232,20,62,233;,
 4;234,21,20,232;,
 4;235,177,176,236;,
 4;237,238,177,235;,
 4;239,37,36,240;,
 4;241,53,52,242;;
 
 MeshMaterialList {
  1;
  128;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\cat_color.jpg";
   }
  }
 }
 MeshNormals {
  132;
  0.199586;0.616403;0.761717;,
  0.185527;0.638654;-0.746794;,
  -0.763190;0.411218;0.498438;,
  -0.810085;0.434374;-0.393803;,
  -0.751610;-0.471309;0.461466;,
  -0.696740;-0.452973;-0.556209;,
  0.186755;-0.695554;0.693777;,
  0.211262;-0.656777;-0.723887;,
  -0.049066;0.621451;0.781915;,
  -0.010197;0.661531;-0.749849;,
  -0.098970;-0.705530;-0.701736;,
  -0.057465;-0.744043;0.665656;,
  0.087400;0.604223;0.792008;,
  0.066476;0.644794;-0.761460;,
  0.055675;-0.673533;-0.737057;,
  0.079127;-0.697239;0.712458;,
  -0.539392;-0.617420;0.572580;,
  -0.481162;-0.518954;-0.706519;,
  -0.631589;0.726531;-0.270645;,
  -0.572475;0.501547;0.648632;,
  0.474060;0.880443;0.009333;,
  0.431149;-0.902015;-0.021885;,
  0.079895;-0.996625;-0.018839;,
  -0.052920;-0.998452;-0.017123;,
  -0.461861;-0.886895;-0.010072;,
  -0.693521;-0.720423;-0.004420;,
  -0.776456;0.629644;0.025766;,
  -0.509152;0.860255;0.026938;,
  -0.072062;0.997182;0.020881;,
  0.065642;0.997700;0.016904;,
  -0.664104;-0.027485;0.747135;,
  -0.999890;-0.007603;0.012705;,
  -0.688128;-0.022857;-0.725229;,
  -0.472582;-0.081174;-0.877540;,
  -0.068324;-0.014441;-0.997559;,
  0.033511;0.011469;-0.999372;,
  0.384573;0.016209;-0.922952;,
  0.999906;0.004673;-0.012895;,
  0.410051;-0.018080;0.911883;,
  0.078884;-0.012159;0.996810;,
  -0.048838;-0.030303;0.998347;,
  -0.450548;-0.011372;0.892680;,
  0.390870;0.832756;0.392095;,
  0.926077;-0.005233;0.377299;,
  0.356783;-0.870617;0.338720;,
  0.081694;-0.955273;0.284217;,
  -0.059049;-0.970995;0.231695;,
  -0.495621;-0.836211;0.234757;,
  -0.699007;-0.649910;0.298340;,
  -0.901162;-0.020763;0.432985;,
  -0.764333;0.564532;0.311607;,
  -0.547651;0.796057;0.257628;,
  -0.061577;0.956825;0.284066;,
  0.080539;0.946506;0.312473;,
  -0.072903;-0.967557;-0.241908;,
  0.071495;-0.976619;-0.202739;,
  0.362629;-0.869346;-0.335764;,
  0.914840;0.008693;-0.403722;,
  0.382454;0.846311;-0.370792;,
  0.073107;0.957852;-0.277805;,
  -0.048216;0.976804;-0.208637;,
  -0.479941;0.876307;-0.041750;,
  -0.785289;0.588650;-0.191868;,
  -0.910601;-0.005733;-0.413246;,
  -0.690785;-0.600470;-0.402804;,
  -0.498494;-0.730793;-0.466311;,
  -0.153326;0.610441;0.777080;,
  -0.153810;0.954864;0.254119;,
  -0.150477;0.988385;0.021259;,
  -0.116086;0.991457;-0.059469;,
  -0.079208;0.988154;-0.131443;,
  -0.125698;-0.077742;-0.989018;,
  -0.148305;-0.649165;-0.746050;,
  -0.132052;-0.925431;-0.355160;,
  -0.123679;-0.992192;-0.016100;,
  -0.122429;-0.967999;0.219063;,
  -0.129564;-0.751508;0.646876;,
  -0.098423;-0.009794;0.995096;,
  0.006947;-0.690258;-0.723530;,
  0.017701;0.009694;-0.999796;,
  0.050430;0.635763;-0.770235;,
  0.058790;0.952467;-0.298917;,
  0.051658;0.998509;0.017615;,
  0.065326;0.940413;0.333701;,
  0.069901;0.595272;0.800478;,
  0.041639;-0.021530;0.998901;,
  0.067556;-0.703850;0.707129;,
  0.064434;-0.949174;0.308085;,
  0.061418;-0.997939;-0.018583;,
  0.033384;-0.969989;-0.240847;,
  -0.693078;0.268121;0.669145;,
  -0.830960;0.360526;0.423705;,
  -0.945499;0.325143;0.017701;,
  -0.880118;0.323690;-0.347301;,
  -0.758245;0.214436;-0.615697;,
  -0.496966;0.031451;-0.867200;,
  -0.089311;-0.014295;-0.995901;,
  -0.027106;0.124748;-0.991818;,
  0.028501;0.212020;-0.976850;,
  0.043763;0.206146;-0.977542;,
  0.333571;0.303188;-0.892640;,
  0.827693;0.364066;-0.427060;,
  0.948248;0.317458;-0.006791;,
  0.838636;0.350193;0.417199;,
  0.353227;0.275285;0.894119;,
  0.076392;0.174605;0.981671;,
  0.050712;0.151588;0.987142;,
  -0.049054;0.094174;0.994346;,
  -0.115207;0.103080;0.987979;,
  -0.484987;0.161269;0.859523;,
  0.343885;-0.355473;0.869128;,
  0.816128;-0.411112;0.406105;,
  0.930923;-0.364733;-0.018740;,
  0.805213;-0.394580;-0.442649;,
  0.328307;-0.273792;-0.904020;,
  0.035951;-0.136289;-0.990017;,
  0.013834;-0.193258;-0.981051;,
  -0.093057;-0.218614;-0.971364;,
  -0.162245;-0.255586;-0.953075;,
  -0.506504;-0.323176;-0.799382;,
  -0.682579;-0.359089;-0.636507;,
  -0.792960;-0.431140;-0.430503;,
  -0.914511;-0.404539;0.004211;,
  -0.783955;-0.445357;0.432518;,
  -0.681774;-0.329292;0.653262;,
  -0.502557;-0.275877;0.819347;,
  -0.123777;-0.282469;0.951257;,
  -0.050442;-0.259682;0.964376;,
  0.063313;-0.301594;0.951332;,
  0.083995;-0.292553;0.952553;,
  -0.065300;0.186032;-0.980371;,
  -0.174197;0.140852;-0.974585;;
  128;
  4;27,68,69,61;,
  4;121,122,31,63;,
  4;73,74,24,65;,
  4;112,113,57,37;,
  4;33,71,118,119;,
  4;125,126,77,41;,
  4;81,82,29,59;,
  4;115,116,79,35;,
  4;22,88,89,55;,
  4;128,129,39,85;,
  4;29,20,58,59;,
  4;35,36,114,115;,
  4;21,22,55,56;,
  4;129,110,38,39;,
  4;24,25,64,65;,
  4;32,33,119,120;,
  4;26,27,61,62;,
  4;124,125,41,30;,
  4;43,111,112,37;,
  4;44,45,22,21;,
  4;45,87,88,22;,
  4;74,75,47,24;,
  4;47,48,25,24;,
  4;122,123,49,31;,
  4;50,51,27,26;,
  4;51,67,68,27;,
  4;82,83,53,29;,
  4;53,42,20,29;,
  4;49,91,92,31;,
  4;92,93,63,31;,
  4;94,95,33,32;,
  4;95,96,71,33;,
  4;98,99,35,79;,
  4;99,100,36,35;,
  4;101,102,37,57;,
  4;102,103,43,37;,
  4;39,38,104,105;,
  4;105,106,85,39;,
  4;41,77,108,109;,
  4;30,41,109,90;,
  4;38,43,103,104;,
  4;110,111,43,38;,
  4;15,45,44,6;,
  4;86,87,45,15;,
  4;16,47,75,76;,
  4;4,48,47,16;,
  4;30,49,123,124;,
  4;90,91,49,30;,
  4;19,51,50,2;,
  4;66,67,51,19;,
  4;12,53,83,84;,
  4;0,42,53,12;,
  4;55,89,78,14;,
  4;56,55,14,7;,
  4;36,57,113,114;,
  4;100,101,57,36;,
  4;59,58,1,13;,
  4;80,81,59,13;,
  4;61,69,70,18;,
  4;62,61,18,3;,
  4;32,63,93,94;,
  4;120,121,63,32;,
  4;65,64,5,17;,
  4;72,73,65,17;,
  4;8,52,67,66;,
  4;68,67,52,28;,
  4;69,68,28,60;,
  4;70,69,60,9;,
  4;96,97,34,71;,
  4;117,118,71,34;,
  4;54,73,72,10;,
  4;23,74,73,54;,
  4;46,75,74,23;,
  4;76,75,46,11;,
  4;126,127,40,77;,
  4;107,108,77,40;,
  4;34,79,116,117;,
  4;97,98,79,34;,
  4;60,81,80,9;,
  4;28,82,81,60;,
  4;52,83,82,28;,
  4;84,83,52,8;,
  4;40,85,106,107;,
  4;127,128,85,40;,
  4;11,46,87,86;,
  4;88,87,46,23;,
  4;89,88,23,54;,
  4;78,89,54,10;,
  4;2,50,91,90;,
  4;92,91,50,26;,
  4;62,93,92,26;,
  4;94,93,62,3;,
  4;18,95,94,3;,
  4;130,96,95,131;,
  4;9,97,96,130;,
  4;80,98,97,9;,
  4;13,99,98,80;,
  4;1,100,99,13;,
  4;58,101,100,1;,
  4;20,102,101,58;,
  4;42,103,102,20;,
  4;104,103,42,0;,
  4;105,104,0,12;,
  4;84,106,105,12;,
  4;107,106,84,8;,
  4;66,108,107,8;,
  4;109,108,66,19;,
  4;90,109,19,2;,
  4;6,44,111,110;,
  4;112,111,44,21;,
  4;56,113,112,21;,
  4;114,113,56,7;,
  4;115,114,7,14;,
  4;78,116,115,14;,
  4;117,116,78,10;,
  4;72,118,117,10;,
  4;119,118,72,17;,
  4;120,119,17,5;,
  4;64,121,120,5;,
  4;25,122,121,64;,
  4;48,123,122,25;,
  4;124,123,48,4;,
  4;16,125,124,4;,
  4;76,126,125,16;,
  4;11,127,126,76;,
  4;86,128,127,11;,
  4;15,129,128,86;,
  4;6,110,129,15;;
 }
 MeshTextureCoords {
  243;
  0.500047;0.535260;,
  0.500047;0.540629;,
  0.513641;0.540629;,
  0.513641;0.535260;,
  0.513641;0.871884;,
  0.500047;0.871884;,
  0.500047;0.883685;,
  0.513641;0.883685;,
  0.513641;0.843906;,
  0.500047;0.843906;,
  0.500047;0.849275;,
  0.513641;0.849275;,
  0.500047;0.834062;,
  0.513641;0.834062;,
  0.513641;0.822260;,
  0.500047;0.822260;,
  0.546371;0.919830;,
  0.546371;0.925199;,
  0.558172;0.925199;,
  0.558172;0.919830;,
  0.441828;0.919830;,
  0.441828;0.925199;,
  0.453629;0.925199;,
  0.453629;0.919830;,
  0.513641;0.847138;,
  0.500047;0.847138;,
  0.500047;0.852940;,
  0.513641;0.852940;,
  0.558172;0.852940;,
  0.558172;0.847138;,
  0.546371;0.847138;,
  0.546371;0.852940;,
  0.500047;0.792759;,
  0.500047;0.798561;,
  0.513641;0.798561;,
  0.513641;0.792759;,
  0.441828;0.938976;,
  0.441828;0.944777;,
  0.453629;0.944777;,
  0.453629;0.938976;,
  0.500047;0.972624;,
  0.500047;0.980654;,
  0.513641;0.980654;,
  0.513641;0.972624;,
  0.546371;0.233164;,
  0.546371;0.241194;,
  0.558172;0.241194;,
  0.558172;0.233164;,
  0.500047;0.844144;,
  0.500047;0.852175;,
  0.513641;0.852175;,
  0.513641;0.844144;,
  0.441828;0.972624;,
  0.441828;0.980654;,
  0.453629;0.980654;,
  0.453629;0.972624;,
  0.500047;0.861801;,
  0.513641;0.861801;,
  0.546371;0.907304;,
  0.558172;0.907304;,
  0.500047;0.522734;,
  0.513641;0.522734;,
  0.441828;0.907304;,
  0.453629;0.907304;,
  0.486461;0.822260;,
  0.486461;0.834062;,
  0.486461;0.844144;,
  0.486461;0.852175;,
  0.486461;0.824328;,
  0.486461;0.830130;,
  0.500047;0.830130;,
  0.500047;0.824328;,
  0.486461;0.843906;,
  0.486461;0.849275;,
  0.486461;0.861801;,
  0.486461;0.871884;,
  0.486461;0.883685;,
  0.486461;0.907304;,
  0.486461;0.919830;,
  0.500047;0.919830;,
  0.500047;0.907304;,
  0.486461;0.925199;,
  0.500047;0.925199;,
  0.500047;0.938976;,
  0.486461;0.938976;,
  0.486461;0.944777;,
  0.500047;0.944777;,
  0.486461;0.972624;,
  0.486461;0.980654;,
  0.486461;0.894268;,
  0.500047;0.894268;,
  0.513641;0.894268;,
  0.535788;0.907304;,
  0.535788;0.919830;,
  0.535788;0.925199;,
  0.535788;0.847138;,
  0.535788;0.852940;,
  0.535788;0.233164;,
  0.535788;0.241194;,
  0.513641;0.811677;,
  0.500047;0.811677;,
  0.486461;0.811677;,
  0.464212;0.980654;,
  0.464212;0.972624;,
  0.464212;0.944777;,
  0.464212;0.938976;,
  0.464212;0.925199;,
  0.464212;0.919830;,
  0.464212;0.907304;,
  0.477248;0.822260;,
  0.477248;0.811677;,
  0.477248;0.834062;,
  0.477248;0.852175;,
  0.477248;0.844144;,
  0.477248;0.830130;,
  0.477248;0.824328;,
  0.477248;0.849275;,
  0.477248;0.843906;,
  0.477248;0.861801;,
  0.477248;0.883685;,
  0.477248;0.871884;,
  0.477248;0.894268;,
  0.477248;0.919830;,
  0.477248;0.907304;,
  0.477248;0.925199;,
  0.477248;0.944777;,
  0.477248;0.938976;,
  0.477248;0.980654;,
  0.477248;0.972624;,
  0.522752;0.798561;,
  0.522752;0.792759;,
  0.522752;0.852175;,
  0.522752;0.844144;,
  0.522752;0.153902;,
  0.513641;0.153902;,
  0.513641;0.165704;,
  0.522752;0.165704;,
  0.522752;0.143319;,
  0.513641;0.143319;,
  0.522752;0.980654;,
  0.522752;0.972624;,
  0.522752;0.847138;,
  0.522752;0.852940;,
  0.522752;0.540629;,
  0.522752;0.535260;,
  0.522752;0.522734;,
  0.522752;0.883685;,
  0.522752;0.894268;,
  0.522752;0.871884;,
  0.522752;0.861801;,
  0.522752;0.849275;,
  0.522752;0.843906;,
  0.477248;0.930951;,
  0.486461;0.930951;,
  0.500047;0.930951;,
  0.500047;0.546381;,
  0.513641;0.546381;,
  0.522752;0.546381;,
  0.535788;0.930951;,
  0.546371;0.930951;,
  0.558172;0.572210;,
  0.558172;0.566458;,
  0.546371;0.566458;,
  0.546371;0.572210;,
  0.513641;0.901293;,
  0.513641;0.907045;,
  0.522752;0.907045;,
  0.522752;0.901293;,
  0.500047;0.189550;,
  0.500047;0.195302;,
  0.513641;0.195302;,
  0.513641;0.189550;,
  0.486461;0.189550;,
  0.486461;0.195302;,
  0.486461;0.838154;,
  0.477248;0.838154;,
  0.441828;0.549239;,
  0.441828;0.554990;,
  0.453629;0.554990;,
  0.453629;0.549239;,
  0.464212;0.554990;,
  0.464212;0.549239;,
  0.546371;0.554990;,
  0.546371;0.563015;,
  0.558172;0.563015;,
  0.558172;0.554990;,
  0.535788;0.938976;,
  0.546371;0.938976;,
  0.513641;0.930951;,
  0.513641;0.938976;,
  0.522752;0.938976;,
  0.522752;0.930951;,
  0.453629;0.563015;,
  0.464212;0.563015;,
  0.441828;0.510951;,
  0.441828;0.518976;,
  0.453629;0.518976;,
  0.453629;0.510951;,
  0.500047;0.838154;,
  0.513641;0.830130;,
  0.513641;0.838154;,
  0.522752;0.893268;,
  0.513641;0.893268;,
  0.513641;0.907304;,
  0.522752;0.907304;,
  0.535788;0.535260;,
  0.535788;0.522734;,
  0.535788;0.540629;,
  0.535788;0.546381;,
  0.535788;0.980654;,
  0.535788;0.972624;,
  0.513641;0.798641;,
  0.522752;0.811677;,
  0.522752;0.798641;,
  0.500047;0.798641;,
  0.486461;0.798641;,
  0.477248;0.798641;,
  0.464212;0.930951;,
  0.522752;0.834062;,
  0.558172;0.972624;,
  0.558172;0.980654;,
  0.568255;0.980654;,
  0.568255;0.972624;,
  0.568255;0.847138;,
  0.568255;0.852940;,
  0.558172;0.580235;,
  0.568255;0.580235;,
  0.568255;0.572210;,
  0.568255;0.566458;,
  0.568255;0.925199;,
  0.568255;0.919830;,
  0.568255;0.907304;,
  0.431745;0.919830;,
  0.431745;0.907304;,
  0.431745;0.925199;,
  0.431745;0.554990;,
  0.431745;0.549239;,
  0.431745;0.563015;,
  0.441828;0.563015;,
  0.431745;0.944777;,
  0.431745;0.938976;,
  0.431745;0.980654;,
  0.431745;0.972624;;
 }
}
