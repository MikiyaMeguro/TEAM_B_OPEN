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
 259;
 0.63936;-1.43197;-0.69134;,
 -0.82498;-1.43197;-0.69134;,
 -0.82498;14.34285;-0.69134;,
 0.63936;14.34285;-0.69134;,
 -0.82498;14.34285;0.02087;,
 0.63936;14.34285;0.02087;,
 -0.82498;-1.43197;0.02087;,
 0.63936;-1.43197;0.02087;,
 -0.82498;-1.43197;-0.69134;,
 0.63936;-1.43197;-0.69134;,
 -0.82498;-1.43197;0.02087;,
 -0.82498;14.34285;0.02087;,
 0.63936;-1.43197;0.02087;,
 0.63936;14.34285;0.02087;,
 -0.09041;21.69707;-0.75227;,
 -0.09600;18.92274;-0.75227;,
 -1.31205;17.50187;-0.75227;,
 -1.00824;19.40871;-0.75227;,
 -0.09041;21.69707;0.08179;,
 -1.00824;19.40871;0.08179;,
 -1.31205;17.50187;0.08179;,
 -0.09600;18.92274;0.08179;,
 -0.09467;12.81898;-0.65516;,
 -0.09467;12.81898;-0.01531;,
 -1.10271;12.81898;-0.01531;,
 -1.10271;12.81898;-0.65516;,
 -1.31205;17.50187;0.08179;,
 -1.00824;19.40871;0.08179;,
 1.09469;17.50187;0.08179;,
 1.09469;17.50187;-0.75227;,
 0.79087;19.40871;-0.75227;,
 0.79087;19.40871;0.08179;,
 0.88535;12.81898;-0.01531;,
 0.88535;12.81898;-0.65516;,
 0.79087;19.40871;0.08179;,
 1.09469;17.50187;0.08179;,
 1.16003;14.16286;-0.75912;,
 -0.09329;17.07864;-0.75227;,
 -1.37739;14.16286;-0.75912;,
 -1.37739;14.16286;0.08865;,
 -1.37739;14.16286;0.08865;,
 -0.09329;17.07864;0.08179;,
 1.16003;14.16286;0.08865;,
 1.16003;14.16286;0.08865;,
 0.88535;12.81898;-0.65516;,
 -0.09467;12.81898;-0.65516;,
 -1.10271;12.81898;-0.65516;,
 -1.10271;12.81898;-0.01531;,
 0.88535;12.81898;-0.01531;,
 -6.19445;15.94693;-0.51842;,
 -4.42911;13.81110;-0.65561;,
 -4.45574;11.94114;-0.66902;,
 -5.43894;13.60102;-0.58879;,
 -6.13798;15.94015;0.31369;,
 -5.38247;13.59425;0.24333;,
 -4.39927;11.93436;0.16310;,
 -4.37264;13.80433;0.17651;,
 -0.52822;9.12004;-0.86120;,
 -0.48490;9.11484;-0.22283;,
 -1.25825;8.46997;-0.17559;,
 -1.30157;8.47517;-0.81396;,
 -4.39927;11.93436;0.16310;,
 -5.38247;13.59425;0.24333;,
 -2.55287;13.47401;0.05032;,
 -2.60934;13.48078;-0.78180;,
 -4.05871;14.75195;-0.67309;,
 -4.00224;14.74518;0.15903;,
 0.26695;9.74178;-0.26875;,
 0.22363;9.74698;-0.90712;,
 -4.00224;14.74518;0.15903;,
 -2.55287;13.47401;0.05032;,
 -0.42988;10.95640;-0.95712;,
 -3.25077;12.39553;-0.74710;,
 -2.37653;9.33315;-0.83822;,
 -2.31913;9.32627;0.00757;,
 -2.31913;9.32627;0.00757;,
 -3.19430;12.38876;0.08502;,
 -0.37248;10.94951;-0.11133;,
 -0.37248;10.94951;-0.11133;,
 0.22363;9.74698;-0.90712;,
 -0.52822;9.12004;-0.86120;,
 -1.30157;8.47517;-0.81396;,
 -1.25825;8.46997;-0.17559;,
 0.26695;9.74178;-0.26875;,
 -8.09991;10.54505;-0.57438;,
 -5.75040;9.07384;-0.68527;,
 -5.18563;7.29098;-0.67513;,
 -6.64260;8.55669;-0.61546;,
 -8.04722;10.56647;0.25774;,
 -6.58992;8.57811;0.21665;,
 -5.13295;7.31240;0.15699;,
 -5.69771;9.09526;0.14685;,
 -0.56797;5.85112;-0.83312;,
 -0.52755;5.86755;-0.19475;,
 -1.05811;5.01223;-0.13914;,
 -1.09853;4.99580;-0.77750;,
 -5.13295;7.31240;0.15699;,
 -6.58992;8.57811;0.21665;,
 -3.86622;9.35451;0.02421;,
 -3.91891;9.33308;-0.80791;,
 -5.69569;10.08322;-0.71472;,
 -5.64300;10.10464;0.11740;,
 -0.01175;6.69909;-0.24882;,
 -0.05217;6.68265;-0.88718;,
 -5.64300;10.10464;0.11740;,
 -3.86622;9.35451;0.02421;,
 -1.05368;7.62340;-0.95219;,
 -4.18530;8.10138;-0.75933;,
 -2.38919;5.47041;-0.81220;,
 -2.33564;5.49219;0.03360;,
 -2.33564;5.49219;0.03360;,
 -4.13261;8.12280;0.07278;,
 -1.00013;7.64517;-0.10639;,
 -1.00013;7.64517;-0.10639;,
 -0.05217;6.68265;-0.88718;,
 -0.56797;5.85112;-0.83312;,
 -1.09853;4.99580;-0.77750;,
 -1.05811;5.01223;-0.13914;,
 -0.01175;6.69909;-0.24882;,
 -8.76549;3.59941;-0.57438;,
 -5.99748;3.44834;-0.68527;,
 -4.64076;2.16116;-0.67513;,
 -6.52819;2.56413;-0.61546;,
 -8.72974;3.64365;0.25774;,
 -6.49244;2.60837;0.21665;,
 -4.60501;2.20539;0.15699;,
 -5.96173;3.49258;0.14685;,
 0.09720;3.13470;-0.83312;,
 0.12462;3.16864;-0.19475;,
 0.07402;2.16340;-0.13914;,
 0.04659;2.12947;-0.77750;,
 -4.60501;2.20539;0.15699;,
 -6.49244;2.60837;0.21665;,
 -4.48419;4.60543;0.02421;,
 -4.51994;4.56120;-0.80791;,
 -6.43788;4.35823;-0.71472;,
 -6.40213;4.40247;0.11740;,
 0.17382;4.14593;-0.24882;,
 0.14639;4.11199;-0.88718;,
 -6.40213;4.40247;0.11740;,
 -4.48419;4.60543;0.02421;,
 -1.18523;4.45087;-0.95219;,
 -4.15727;3.35433;-0.75933;,
 -1.31260;1.92052;-0.81220;,
 -1.27626;1.96548;0.03360;,
 -1.27626;1.96548;0.03360;,
 -4.12152;3.39857;0.07278;,
 -1.14889;4.49584;-0.10639;,
 -1.14889;4.49584;-0.10639;,
 0.14639;4.11199;-0.88718;,
 0.09720;3.13470;-0.83312;,
 0.04659;2.12947;-0.77750;,
 0.07402;2.16340;-0.13914;,
 0.17382;4.14593;-0.24882;,
 6.18048;15.94693;-0.17270;,
 4.41925;13.81110;0.00981;,
 4.44622;11.94114;0.02253;,
 5.42703;13.60102;-0.08294;,
 6.10264;15.94015;-1.00309;,
 5.34919;13.59425;-0.91334;,
 4.36838;11.93436;-0.80786;,
 4.34142;13.80433;-0.82058;,
 0.52493;9.12004;0.31558;,
 0.46522;9.11484;-0.32146;,
 1.23710;8.46997;-0.38855;,
 1.29681;8.47517;0.24849;,
 4.36838;11.93436;-0.80786;,
 5.34919;13.59425;-0.91334;,
 2.52549;13.47401;-0.64767;,
 2.60333;13.48078;0.18273;,
 4.04942;14.75195;0.03681;,
 3.97158;14.74518;-0.79359;,
 -0.28520;9.74178;-0.25623;,
 -0.22548;9.74698;0.38081;,
 3.97158;14.74518;-0.79359;,
 2.52549;13.47401;-0.64767;,
 0.42909;10.95640;0.41401;,
 3.24365;12.39553;0.13155;,
 2.37204;9.33315;0.24511;,
 2.29293;9.32627;-0.59892;,
 2.29293;9.32627;-0.59892;,
 3.16581;12.38876;-0.69884;,
 0.34997;10.94951;-0.43003;,
 0.34997;10.94951;-0.43003;,
 -0.22548;9.74698;0.38081;,
 0.52493;9.12004;0.31558;,
 1.29681;8.47517;0.24849;,
 1.23710;8.46997;-0.38855;,
 -0.28520;9.74178;-0.25623;,
 8.08675;10.54505;-0.16574;,
 5.74086;9.07384;0.00550;,
 5.17603;7.29098;0.00988;,
 6.63098;8.55669;-0.08721;,
 8.01270;10.56647;-0.99623;,
 6.55692;8.57811;-0.91770;,
 5.10197;7.31240;-0.82061;,
 5.66680;9.09526;-0.82499;,
 0.56395;5.85112;0.28649;,
 0.50714;5.86755;-0.35062;,
 1.03609;5.01223;-0.41985;,
 1.09291;4.99580;0.21726;,
 5.10197;7.31240;-0.82061;,
 6.55692;8.57811;-0.91770;,
 3.83907;9.35451;-0.65532;,
 3.91313;9.33308;0.17517;,
 5.68693;10.08322;0.03635;,
 5.61288;10.10464;-0.79414;,
 -0.00711;6.69909;-0.28332;,
 0.04971;6.68265;0.35380;,
 5.61288;10.10464;-0.79414;,
 3.83907;9.35451;-0.65532;,
 1.05256;7.62340;0.39304;,
 4.17818;8.10138;0.11977;,
 2.38403;5.47041;0.21877;,
 2.30876;5.49219;-0.62536;,
 2.30876;5.49219;-0.62536;,
 4.10413;8.12280;-0.71072;,
 0.97729;7.64517;-0.45110;,
 0.97729;7.64517;-0.45110;,
 0.04971;6.68265;0.35380;,
 0.56395;5.85112;0.28649;,
 1.09291;4.99580;0.21726;,
 1.03609;5.01223;-0.41985;,
 -0.00711;6.69909;-0.28332;,
 8.75211;3.59941;-0.18284;,
 5.98786;3.44834;-0.00085;,
 4.63133;2.16116;0.02389;,
 6.51661;2.56413;-0.08427;,
 8.69498;3.64365;-1.01377;,
 6.45948;2.60837;-0.91520;,
 4.57421;2.20539;-0.80704;,
 5.93074;3.49258;-0.83177;,
 -0.10100;3.13470;0.30359;,
 -0.14482;3.16864;-0.33386;,
 -0.09567;2.16340;-0.39076;,
 -0.05184;2.12947;0.24669;,
 4.57421;2.20539;-0.80704;,
 6.45948;2.60837;-0.91520;,
 4.45684;4.60543;-0.67120;,
 4.51397;4.56120;0.15973;,
 6.42888;4.35823;0.01727;,
 6.37175;4.40247;-0.81365;,
 -0.19261;4.14593;-0.27855;,
 -0.14879;4.11199;0.35890;,
 6.37175;4.40247;-0.81365;,
 4.45684;4.60543;-0.67120;,
 1.18406;4.45087;0.38966;,
 4.15017;3.35433;0.12049;,
 1.30779;1.92052;0.24644;,
 1.24973;1.96548;-0.59814;,
 1.24973;1.96548;-0.59814;,
 4.09304;3.39857;-0.71044;,
 1.12600;4.49584;-0.45492;,
 1.12600;4.49584;-0.45492;,
 -0.14879;4.11199;0.35890;,
 -0.10100;3.13470;0.30359;,
 -0.05184;2.12947;0.24669;,
 -0.09567;2.16340;-0.39076;,
 -0.19261;4.14593;-0.27855;;
 
 160;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;1,10,11,2;,
 4;12,0,3,13;,
 4;14,15,16,17;,
 4;18,14,17,19;,
 4;20,21,18,19;,
 4;22,23,24,25;,
 4;16,26,27,17;,
 4;28,29,30,31;,
 4;32,23,22,33;,
 4;34,18,21,35;,
 4;30,14,18,34;,
 4;29,15,14,30;,
 4;36,37,15,29;,
 4;16,15,37,38;,
 4;38,39,26,16;,
 4;40,41,21,20;,
 4;35,21,41,42;,
 4;43,36,29,28;,
 4;44,45,37,36;,
 4;38,37,45,46;,
 4;46,47,39,38;,
 4;23,41,40,24;,
 4;42,41,23,32;,
 4;48,44,36,43;,
 4;49,50,51,52;,
 4;53,49,52,54;,
 4;55,56,53,54;,
 4;57,58,59,60;,
 4;51,61,62,52;,
 4;63,64,65,66;,
 4;67,58,57,68;,
 4;69,53,56,70;,
 4;65,49,53,69;,
 4;64,50,49,65;,
 4;71,72,50,64;,
 4;51,50,72,73;,
 4;73,74,61,51;,
 4;75,76,56,55;,
 4;70,56,76,77;,
 4;78,71,64,63;,
 4;79,80,72,71;,
 4;73,72,80,81;,
 4;81,82,74,73;,
 4;58,76,75,59;,
 4;77,76,58,67;,
 4;83,79,71,78;,
 4;84,85,86,87;,
 4;88,84,87,89;,
 4;90,91,88,89;,
 4;92,93,94,95;,
 4;86,96,97,87;,
 4;98,99,100,101;,
 4;102,93,92,103;,
 4;104,88,91,105;,
 4;100,84,88,104;,
 4;99,85,84,100;,
 4;106,107,85,99;,
 4;86,85,107,108;,
 4;108,109,96,86;,
 4;110,111,91,90;,
 4;105,91,111,112;,
 4;113,106,99,98;,
 4;114,115,107,106;,
 4;108,107,115,116;,
 4;116,117,109,108;,
 4;93,111,110,94;,
 4;112,111,93,102;,
 4;118,114,106,113;,
 4;119,120,121,122;,
 4;123,119,122,124;,
 4;125,126,123,124;,
 4;127,128,129,130;,
 4;121,131,132,122;,
 4;133,134,135,136;,
 4;137,128,127,138;,
 4;139,123,126,140;,
 4;135,119,123,139;,
 4;134,120,119,135;,
 4;141,142,120,134;,
 4;121,120,142,143;,
 4;143,144,131,121;,
 4;145,146,126,125;,
 4;140,126,146,147;,
 4;148,141,134,133;,
 4;149,150,142,141;,
 4;143,142,150,151;,
 4;151,152,144,143;,
 4;128,146,145,129;,
 4;147,146,128,137;,
 4;153,149,141,148;,
 4;154,155,156,157;,
 4;158,154,157,159;,
 4;160,161,158,159;,
 4;162,163,164,165;,
 4;156,166,167,157;,
 4;168,169,170,171;,
 4;172,163,162,173;,
 4;174,158,161,175;,
 4;170,154,158,174;,
 4;169,155,154,170;,
 4;176,177,155,169;,
 4;156,155,177,178;,
 4;178,179,166,156;,
 4;180,181,161,160;,
 4;175,161,181,182;,
 4;183,176,169,168;,
 4;184,185,177,176;,
 4;178,177,185,186;,
 4;186,187,179,178;,
 4;163,181,180,164;,
 4;182,181,163,172;,
 4;188,184,176,183;,
 4;189,190,191,192;,
 4;193,189,192,194;,
 4;195,196,193,194;,
 4;197,198,199,200;,
 4;191,201,202,192;,
 4;203,204,205,206;,
 4;207,198,197,208;,
 4;209,193,196,210;,
 4;205,189,193,209;,
 4;204,190,189,205;,
 4;211,212,190,204;,
 4;191,190,212,213;,
 4;213,214,201,191;,
 4;215,216,196,195;,
 4;210,196,216,217;,
 4;218,211,204,203;,
 4;219,220,212,211;,
 4;213,212,220,221;,
 4;221,222,214,213;,
 4;198,216,215,199;,
 4;217,216,198,207;,
 4;223,219,211,218;,
 4;224,225,226,227;,
 4;228,224,227,229;,
 4;230,231,228,229;,
 4;232,233,234,235;,
 4;226,236,237,227;,
 4;238,239,240,241;,
 4;242,233,232,243;,
 4;244,228,231,245;,
 4;240,224,228,244;,
 4;239,225,224,240;,
 4;246,247,225,239;,
 4;226,225,247,248;,
 4;248,249,236,226;,
 4;250,251,231,230;,
 4;245,231,251,252;,
 4;253,246,239,238;,
 4;254,255,247,246;,
 4;248,247,255,256;,
 4;256,257,249,248;,
 4;233,251,250,234;,
 4;252,251,233,242;,
 4;258,254,246,253;;
 
 MeshMaterialList {
  1;
  160;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\Cannabis.jpg";
   }
  }
 }
 MeshNormals {
  256;
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;0.000000;,
  0.965665;0.259791;0.000000;,
  -0.963845;0.266462;0.000000;,
  -0.928129;0.372260;0.000000;,
  0.996061;0.088668;0.000000;,
  -0.000002;0.000509;-1.000000;,
  0.000177;0.000509;-1.000000;,
  0.000177;0.000510;1.000000;,
  -0.000002;0.000510;1.000000;,
  -0.014785;-0.024486;-0.999591;,
  -0.000166;-0.024494;-0.999700;,
  0.014453;-0.024496;-0.999596;,
  -0.995860;-0.090899;0.000000;,
  -0.000166;-0.024492;0.999700;,
  -0.014786;-0.024485;0.999591;,
  0.637851;-0.768564;-0.049546;,
  0.637852;-0.768564;-0.049546;,
  0.575127;0.817424;-0.032377;,
  -0.067705;0.008121;-0.997672;,
  -0.909403;-0.411801;0.058362;,
  0.637852;-0.768564;-0.049546;,
  -0.949484;-0.307644;0.061930;,
  -0.067706;0.008121;-0.997672;,
  0.707597;0.705350;-0.042280;,
  -0.068034;0.008510;-0.997647;,
  -0.067896;0.008624;-0.997655;,
  0.067518;-0.007614;0.997689;,
  0.067380;-0.007729;0.997697;,
  -0.063404;-0.020159;-0.997784;,
  -0.052194;-0.010813;-0.998578;,
  -0.040972;-0.001465;-0.999159;,
  -0.706021;-0.706935;0.042159;,
  0.083182;-0.027046;0.996167;,
  0.071955;-0.036393;0.996744;,
  0.847937;-0.528580;-0.040081;,
  0.847934;-0.528585;-0.040085;,
  0.287966;0.956681;-0.042863;,
  -0.063173;-0.025687;-0.997672;,
  -0.733238;-0.676968;0.063849;,
  0.847935;-0.528582;-0.040083;,
  -0.804148;-0.590741;0.066121;,
  -0.063172;-0.025686;-0.997672;,
  0.449066;0.892019;-0.051400;,
  -0.063605;-0.025418;-0.997652;,
  -0.063510;-0.025266;-0.997661;,
  0.062831;0.026104;0.997683;,
  0.062737;0.025951;0.997693;,
  -0.050164;-0.051162;-0.997430;,
  -0.042471;-0.038765;-0.998345;,
  -0.034768;-0.026359;-0.999048;,
  -0.447067;-0.893029;0.051296;,
  0.083834;0.012588;0.996400;,
  0.076125;0.000183;0.997098;,
  0.997819;-0.052446;-0.040079;,
  0.997819;-0.052449;-0.040079;,
  -0.210751;0.976600;-0.042864;,
  -0.042865;-0.053044;-0.997672;,
  -0.314264;-0.947186;0.063856;,
  0.997819;-0.052447;-0.040079;,
  -0.418035;-0.906021;0.066129;,
  -0.042864;-0.053041;-0.997672;,
  -0.038474;0.997937;-0.051398;,
  -0.043372;-0.053015;-0.997651;,
  -0.043364;-0.052837;-0.997661;,
  0.042362;0.053237;0.997683;,
  0.042354;0.053059;0.997693;,
  -0.019155;-0.069044;-0.997430;,
  -0.018419;-0.054472;-0.998345;,
  -0.017679;-0.039889;-0.999048;,
  0.040711;-0.997854;0.051291;,
  0.067283;0.051571;0.996400;,
  0.066537;0.036985;0.997098;,
  -0.636370;-0.768561;0.065926;,
  -0.636369;-0.768563;0.065921;,
  -0.574105;0.817423;0.047149;,
  0.093318;0.008122;0.995603;,
  0.907603;-0.411800;-0.081717;,
  -0.636370;-0.768562;0.065923;,
  0.947579;-0.307643;-0.086314;,
  0.093324;0.008118;0.995603;,
  -0.706277;0.705349;0.060453;,
  0.093652;0.008508;0.995569;,
  0.093510;0.008625;0.995581;,
  -0.093140;-0.007613;-0.995624;,
  -0.092999;-0.007730;-0.995636;,
  0.089030;-0.020165;0.995825;,
  0.077841;-0.010815;0.996907;,
  0.066634;-0.001462;0.997776;,
  0.704704;-0.706936;-0.060287;,
  -0.108755;-0.027048;-0.993701;,
  -0.097547;-0.036392;-0.994565;,
  -0.846624;-0.528584;0.061863;,
  -0.846623;-0.528584;0.061867;,
  -0.286769;0.956681;0.050248;,
  0.088785;-0.025679;0.995720;,
  0.731354;-0.676968;-0.082677;,
  -0.846624;-0.528584;0.061865;,
  0.802181;-0.590743;-0.086767;,
  0.088789;-0.025684;0.995719;,
  -0.447596;0.892019;0.062924;,
  0.089223;-0.025416;0.995687;,
  0.089128;-0.025263;0.995700;,
  -0.088452;0.026102;-0.995738;,
  -0.088358;0.025951;-0.995751;,
  0.075784;-0.051160;0.995811;,
  0.068117;-0.038764;0.996924;,
  0.060436;-0.026360;0.997824;,
  0.445601;-0.893028;-0.062772;,
  -0.109413;0.012587;-0.993917;,
  -0.101724;0.000181;-0.994813;,
  -0.996460;-0.052446;0.065707;,
  -0.996459;-0.052446;0.065715;,
  0.211783;0.976600;0.037432;,
  0.068489;-0.053034;0.996241;,
  0.312519;-0.947186;-0.071913;,
  -0.996459;-0.052446;0.065711;,
  0.416198;-0.906021;-0.076853;,
  0.068491;-0.053030;0.996241;,
  0.039782;0.997937;0.050392;,
  0.068999;-0.053009;0.996207;,
  0.068989;-0.052832;0.996217;,
  -0.067992;0.053244;-0.996264;,
  -0.067983;0.053063;-0.996274;,
  0.044785;-0.069043;0.996608;,
  0.044072;-0.054472;0.997542;,
  0.043351;-0.039890;0.998263;,
  -0.042016;-0.997854;-0.050228;,
  -0.092866;0.051571;-0.994342;,
  -0.092139;0.036987;-0.995059;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  -0.996061;0.088666;0.000000;,
  -0.000182;0.000510;1.000000;,
  0.933190;0.359384;0.000000;,
  -0.000181;0.000509;-1.000000;,
  0.014454;-0.024494;0.999596;,
  0.995860;-0.090899;-0.000000;,
  -0.029195;-0.049971;-0.998324;,
  -0.000328;-0.050001;-0.998749;,
  0.028539;-0.049989;-0.998342;,
  -0.979744;-0.200253;0.000000;,
  -0.000328;-0.050000;0.998749;,
  0.028541;-0.049988;0.998342;,
  -0.029197;-0.049969;0.998324;,
  0.979744;-0.200253;-0.000000;,
  0.067706;-0.008119;0.997672;,
  0.067705;-0.008118;0.997672;,
  -0.820712;-0.569056;0.051063;,
  0.067706;-0.008119;0.997672;,
  0.067243;-0.007844;0.997706;,
  0.486686;0.873192;-0.025919;,
  -0.068172;0.008395;-0.997638;,
  -0.067708;0.008121;-0.997672;,
  0.094392;-0.017694;0.995378;,
  0.821981;0.567212;-0.051164;,
  -0.058118;-0.048970;-0.997108;,
  -0.035984;-0.030527;-0.998886;,
  -0.013821;-0.012057;-0.999832;,
  -0.623907;-0.780669;0.035986;,
  0.099262;-0.046745;0.993963;,
  0.121374;-0.028264;0.992204;,
  0.077068;-0.065186;0.994893;,
  0.879369;0.472858;-0.055825;,
  0.063168;0.025683;0.997672;,
  0.063165;0.025681;0.997673;,
  -0.599435;-0.798283;0.058501;,
  0.063170;0.025684;0.997672;,
  0.062642;0.025797;0.997703;,
  0.186425;0.981769;-0.037076;,
  -0.063699;-0.025570;-0.997642;,
  -0.063170;-0.025684;-0.997672;,
  0.091524;0.024991;0.995489;,
  0.601222;0.796931;-0.058585;,
  -0.036058;-0.076824;-0.996392;,
  -0.020867;-0.052360;-0.998410;,
  -0.005660;-0.027852;-0.999596;,
  -0.345858;-0.937158;0.046025;,
  0.105316;-0.001055;0.994438;,
  0.120474;0.023433;0.992440;,
  0.090071;-0.025543;0.995608;,
  0.685465;0.725454;-0.062078;,
  0.042861;0.053031;0.997673;,
  0.042858;0.053025;0.997673;,
  -0.138474;-0.988637;0.058503;,
  0.042863;0.053037;0.997672;,
  0.042346;0.052880;0.997703;,
  -0.311760;0.949437;-0.037083;,
  -0.043381;-0.053193;-0.997642;,
  -0.042863;-0.053037;-0.997672;,
  0.068014;0.066146;0.995489;,
  0.140691;0.988319;-0.058589;,
  0.005605;-0.084680;-0.996392;,
  0.007065;-0.055921;-0.998410;,
  0.008520;-0.027115;-0.999596;,
  0.150636;-0.987518;0.046019;,
  0.092685;0.050021;0.994438;,
  0.094105;0.078787;0.992440;,
  0.091187;0.021214;0.995608;,
  0.248996;0.966512;-0.062087;,
  -0.093326;-0.008120;-0.995602;,
  -0.093332;-0.008116;-0.995602;,
  0.819129;-0.569056;-0.072139;,
  -0.093320;-0.008125;-0.995603;,
  -0.092859;-0.007847;-0.995648;,
  -0.485859;0.873192;0.038420;,
  0.093793;0.008390;0.995556;,
  0.093330;0.008115;0.995602;,
  -0.119940;-0.017698;-0.992623;,
  -0.820395;0.567211;0.072276;,
  0.083727;-0.048978;0.995284;,
  0.061644;-0.030527;0.997631;,
  0.039509;-0.012051;0.999147;,
  0.622775;-0.780671;-0.052005;,
  -0.124774;-0.046747;-0.991083;,
  -0.146830;-0.028271;-0.988758;,
  -0.102613;-0.065184;-0.992583;,
  -0.877645;0.472854;0.078413;,
  -0.088789;0.025684;-0.995719;,
  -0.088786;0.025679;-0.995720;,
  0.597734;-0.798282;-0.073894;,
  -0.088792;0.025689;-0.995719;,
  -0.088264;0.025799;-0.995763;,
  -0.185411;0.981769;0.041853;,
  0.089318;-0.025568;0.995675;,
  0.088792;-0.025688;0.995719;,
  -0.117078;0.024990;-0.992808;,
  -0.599517;0.796932;0.074019;,
  0.061659;-0.076827;0.995136;,
  0.046523;-0.052360;0.997544;,
  0.031349;-0.027850;0.999120;,
  0.344561;-0.937157;-0.054901;,
  -0.130836;-0.001057;-0.991404;,
  -0.145939;0.023434;-0.989016;,
  -0.115623;-0.025547;-0.992965;,
  -0.683642;0.725455;0.079678;,
  -0.068492;0.053041;-0.996241;,
  -0.068493;0.053045;-0.996240;,
  0.136925;-0.988637;-0.062042;,
  -0.068490;0.053036;-0.996241;,
  -0.067973;0.052882;-0.996285;,
  0.312611;0.949437;0.029056;,
  0.069009;-0.053187;0.996197;,
  0.068493;-0.053027;0.996241;,
  -0.093574;0.066145;-0.993413;,
  -0.139139;0.988319;0.062184;,
  0.020006;-0.084680;0.996207;,
  0.018599;-0.055921;0.998262;,
  0.017175;-0.027116;0.999485;,
  -0.151769;-0.987518;-0.042132;,
  -0.118210;0.050023;-0.991728;,
  -0.119578;0.078791;-0.989693;,
  -0.116742;0.021213;-0.992936;,
  -0.247318;0.966513;0.068463;;
  160;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;132,132,132,132;,
  4;133,133,133,133;,
  4;0,8,9,0;,
  4;6,6,5,5;,
  4;10,11,2,2;,
  4;3,3,3,3;,
  4;134,134,5,5;,
  4;7,7,4,4;,
  4;3,3,3,3;,
  4;2,2,11,135;,
  4;4,136,136,4;,
  4;137,8,0,0;,
  4;12,13,8,137;,
  4;9,8,13,14;,
  4;15,15,134,134;,
  4;138,16,11,10;,
  4;135,11,16,17;,
  4;139,139,7,7;,
  4;140,141,13,12;,
  4;14,13,141,142;,
  4;143,143,15,15;,
  4;144,16,138,145;,
  4;17,16,144,146;,
  4;147,147,139,139;,
  4;25,27,28,21;,
  4;24,24,22,22;,
  4;29,30,148,149;,
  4;23,23,19,19;,
  4;150,150,22,22;,
  4;26,26,20,20;,
  4;18,23,23,18;,
  4;151,148,30,152;,
  4;20,153,153,20;,
  4;154,27,25,155;,
  4;31,32,27,154;,
  4;28,27,32,33;,
  4;34,34,150,150;,
  4;156,35,30,29;,
  4;152,30,35,36;,
  4;157,157,26,26;,
  4;158,159,32,31;,
  4;33,32,159,160;,
  4;161,161,34,34;,
  4;162,35,156,163;,
  4;36,35,162,164;,
  4;165,165,157,157;,
  4;44,46,47,40;,
  4;43,43,41,41;,
  4;48,49,166,167;,
  4;42,42,38,38;,
  4;168,168,41,41;,
  4;45,45,39,39;,
  4;37,42,42,37;,
  4;169,166,49,170;,
  4;39,171,171,39;,
  4;172,46,44,173;,
  4;50,51,46,172;,
  4;47,46,51,52;,
  4;53,53,168,168;,
  4;174,54,49,48;,
  4;170,49,54,55;,
  4;175,175,45,45;,
  4;176,177,51,50;,
  4;52,51,177,178;,
  4;179,179,53,53;,
  4;180,54,174,181;,
  4;55,54,180,182;,
  4;183,183,175,175;,
  4;63,65,66,59;,
  4;62,62,60,60;,
  4;67,68,184,185;,
  4;61,61,57,57;,
  4;186,186,60,60;,
  4;64,64,58,58;,
  4;56,61,61,56;,
  4;187,184,68,188;,
  4;58,189,189,58;,
  4;190,65,63,191;,
  4;69,70,65,190;,
  4;66,65,70,71;,
  4;72,72,186,186;,
  4;192,73,68,67;,
  4;188,68,73,74;,
  4;193,193,64,64;,
  4;194,195,70,69;,
  4;71,70,195,196;,
  4;197,197,72,72;,
  4;198,73,192,199;,
  4;74,73,198,200;,
  4;201,201,193,193;,
  4;82,84,85,78;,
  4;81,81,79,79;,
  4;86,87,202,203;,
  4;80,80,76,76;,
  4;204,204,79,79;,
  4;83,83,77,77;,
  4;75,80,80,75;,
  4;205,202,87,206;,
  4;77,207,207,77;,
  4;208,84,82,209;,
  4;88,89,84,208;,
  4;85,84,89,90;,
  4;91,91,204,204;,
  4;210,92,87,86;,
  4;206,87,92,93;,
  4;211,211,83,83;,
  4;212,213,89,88;,
  4;90,89,213,214;,
  4;215,215,91,91;,
  4;216,92,210,217;,
  4;93,92,216,218;,
  4;219,219,211,211;,
  4;101,103,104,97;,
  4;100,100,98,98;,
  4;105,106,220,221;,
  4;99,99,95,95;,
  4;222,222,98,98;,
  4;102,102,96,96;,
  4;94,99,99,94;,
  4;223,220,106,224;,
  4;96,225,225,96;,
  4;226,103,101,227;,
  4;107,108,103,226;,
  4;104,103,108,109;,
  4;110,110,222,222;,
  4;228,111,106,105;,
  4;224,106,111,112;,
  4;229,229,102,102;,
  4;230,231,108,107;,
  4;109,108,231,232;,
  4;233,233,110,110;,
  4;234,111,228,235;,
  4;112,111,234,236;,
  4;237,237,229,229;,
  4;120,122,123,116;,
  4;119,119,117,117;,
  4;124,125,238,239;,
  4;118,118,114,114;,
  4;240,240,117,117;,
  4;121,121,115,115;,
  4;113,118,118,113;,
  4;241,238,125,242;,
  4;115,243,243,115;,
  4;244,122,120,245;,
  4;126,127,122,244;,
  4;123,122,127,128;,
  4;129,129,240,240;,
  4;246,130,125,124;,
  4;242,125,130,131;,
  4;247,247,121,121;,
  4;248,249,127,126;,
  4;128,127,249,250;,
  4;251,251,129,129;,
  4;252,130,246,253;,
  4;131,130,252,254;,
  4;255,255,247,247;;
 }
 MeshTextureCoords {
  259;
  0.462349;0.945559;,
  0.537651;0.945559;,
  0.537651;0.870258;,
  0.462349;0.870258;,
  0.537651;0.794957;,
  0.462349;0.794957;,
  0.537651;0.719655;,
  0.462349;0.719655;,
  0.537651;0.644354;,
  0.462349;0.644354;,
  0.612952;0.945559;,
  0.612952;0.870258;,
  0.387048;0.945559;,
  0.387048;0.870258;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;,
  0.499469;0.870258;,
  0.499469;0.909635;,
  0.537651;0.909635;,
  0.537651;0.870258;,
  0.499469;0.794957;,
  0.537651;0.794957;,
  0.537651;0.755580;,
  0.499469;0.755580;,
  0.499469;0.644354;,
  0.499469;0.719655;,
  0.537651;0.719655;,
  0.537651;0.644354;,
  0.612952;0.909635;,
  0.612952;0.870258;,
  0.387048;0.909635;,
  0.462349;0.909635;,
  0.462349;0.870258;,
  0.387048;0.870258;,
  0.462349;0.719655;,
  0.462349;0.644354;,
  0.462349;0.794957;,
  0.462349;0.755580;,
  0.462349;0.927071;,
  0.499469;0.927071;,
  0.537651;0.927071;,
  0.612952;0.927071;,
  0.537651;0.738143;,
  0.499469;0.738143;,
  0.462349;0.738143;,
  0.387048;0.927071;,
  0.462349;0.945559;,
  0.499469;0.945559;,
  0.537651;0.945559;,
  0.612952;0.945559;,
  0.387048;0.945559;;
 }
}
