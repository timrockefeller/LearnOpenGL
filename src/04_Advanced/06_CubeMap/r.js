let ori = "-0.5f,-0.5f,-0.5f,0.0f,0.0f,0.5f,-0.5f,-0.5f,1.0f,0.0f,0.5f,0.5f,-0.5f,1.0f,1.0f,0.5f,0.5f,-0.5f,1.0f,1.0f,-0.5f,0.5f,-0.5f,0.0f,1.0f,-0.5f,-0.5f,-0.5f,0.0f,0.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,0.5f,-0.5f,0.5f,1.0f,0.0f,0.5f,0.5f,0.5f,1.0f,1.0f,0.5f,0.5f,0.5f,1.0f,1.0f,-0.5f,0.5f,0.5f,0.0f,1.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,-0.5f,0.5f,0.5f,1.0f,0.0f,-0.5f,0.5f,-0.5f,1.0f,1.0f,-0.5f,-0.5f,-0.5f,0.0f,1.0f,-0.5f,-0.5f,-0.5f,0.0f,1.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,-0.5f,0.5f,0.5f,1.0f,0.0f,0.5f,0.5f,0.5f,1.0f,0.0f,0.5f,0.5f,-0.5f,1.0f,1.0f,0.5f,-0.5f,-0.5f,0.0f,1.0f,0.5f,-0.5f,-0.5f,0.0f,1.0f,0.5f,-0.5f,0.5f,0.0f,0.0f,0.5f,0.5f,0.5f,1.0f,0.0f,-0.5f,-0.5f,-0.5f,0.0f,1.0f,0.5f,-0.5f,-0.5f,1.0f,1.0f,0.5f,-0.5f,0.5f,1.0f,0.0f,0.5f,-0.5f,0.5f,1.0f,0.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,-0.5f,-0.5f,-0.5f,0.0f,1.0f,-0.5f,0.5f,-0.5f,0.0f,1.0f,0.5f,0.5f,-0.5f,1.0f,1.0f,0.5f,0.5f,0.5f,1.0f,0.0f,0.5f,0.5f,0.5f,1.0f,0.0f,-0.5f,0.5f,0.5f,0.0f,0.0f,-0.5f,0.5f,-0.5f,0.0f,1.0f";
let las = "-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,-0.5f,0.5f,-0.5f,0.0f,0.0f,-1.0f,-0.5f,-0.5f,-0.5f,0.0f,0.0f,-1.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,-0.5f,0.5f,0.5f,0.0f,0.0f,1.0f,-0.5f,-0.5f,0.5f,0.0f,0.0f,1.0f,-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,-0.5f,0.5f,-0.5f,-1.0f,0.0f,0.0f,-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,-0.5f,-0.5f,-0.5f,-1.0f,0.0f,0.0f,-0.5f,-0.5f,0.5f,-1.0f,0.0f,0.0f,-0.5f,0.5f,0.5f,-1.0f,0.0f,0.0f,0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,0.5f,0.5f,-0.5f,1.0f,0.0f,0.0f,0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.5f,-0.5f,-0.5f,1.0f,0.0f,0.0f,0.5f,-0.5f,0.5f,1.0f,0.0f,0.0f,0.5f,0.5f,0.5f,1.0f,0.0f,0.0f,-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,-0.5f,-0.5f,0.5f,0.0f,-1.0f,0.0f,-0.5f,-0.5f,-0.5f,0.0f,-1.0f,0.0f,-0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f,0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,-0.5f,0.5f,0.5f,0.0f,1.0f,0.0f,-0.5f,0.5f,-0.5f,0.0f,1.0f,0.0f";




let os = ori.split(",");
let ls = las.split(",");
let rs = [];
for (let i = 0; i < 36; i++) {
    rs.push(os[5 * i + 0]);
    rs.push(os[5 * i + 1]);
    rs.push(os[5 * i + 2]);
    rs.push(os[5 * i + 3]);
    rs.push(os[5 * i + 4]);
    rs.push(ls[6 * i + 3]);
    rs.push(ls[6 * i + 4]);
    rs.push(ls[6 * i + 5]);
}

console.log(rs.join(","));
