#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // bikin graf dalam bentuk adjacency list
        vector<vector<pair<int,double>>> g(n);
        for (int i=0; i<edges.size(); i++){
            int u = edges[i][0]; // node awal
            int v = edges[i][1]; // node tujuan
            double w = -log(succProb[i]); // ubah prob ke bentuk jarak log
            g[u].push_back({v,w}); // simpan ke adjacency list arah u->v
            g[v].push_back({u,w}); // karena grafnya dua arah, simpan juga v->u
        }

        // nyiapin jarak awal semua node = tak hingga
        vector<double> dist(n, numeric_limits<double>::infinity());
        dist[start] = 0; // jarak dari start ke dirinya sendiri = 0

        // nyimpen jalur yang dilewati (buat rekonstruksi nanti)
        vector<int> parent(n, -1);

        // priority queue buat dijkstra (menyimpan pasangan (jarak, node))
        priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
        pq.push({0, start}); // mulai dari node awal

        // mulai proses dijkstra
        while(!pq.empty()){
            auto [d, node] = pq.top(); // ambil node dengan jarak paling kecil
            pq.pop(); // keluarin dari queue

            if(d > dist[node]) continue; // kalau udah ada yang lebih baik, skip

            if(node == end) break; // kalau udah sampai tujuan, boleh berhenti

            // cek semua tetangga node ini
            for(auto &[next, w] : g[node]){
                double nd = d + w; // hitung jarak baru
                if(nd < dist[next]){ // kalau jarak baru lebih kecil
                    dist[next] = nd; // update jarak
                    parent[next] = node; // catat parent-nya
                    pq.push({nd, next}); // masukin ke queue buat diproses
                }
            }
        }

        // kalau end gak pernah dikunjungi, berarti gak ada jalur
        if(dist[end] == numeric_limits<double>::infinity()){
            cout << "gak ada jalur dari " << start << " ke " << end << endl;
            return 0.0;
        }

        // rekonstruksi jalur dari end ke start pakai parent
        vector<int> path;
        for(int cur = end; cur != -1; cur = parent[cur])
            path.push_back(cur); // tambah node ke jalur
        reverse(path.begin(), path.end()); // dibalik biar urut dari start ke end

        // tampilkan hasil jalurnya
        cout << "jalur terbaik: ";
        for(int i=0; i<path.size(); i++){
            cout << path[i];
            if(i < path.size()-1) cout << " -> "; // kasih panah antar node
        }
        cout << endl;

        // ubah lagi hasil -log jadi probabilitas asli
        double ans = exp(-dist[end]);

        // print hasil probabilitas
        cout << "probabilitas maksimum: " << fixed << setprecision(6) << ans << endl;

        return ans; // kembalikan hasilnya
    }
};

int main(){
    int n = 5; // jumlah node
    vector<vector<int>> edges = {
        {0,1},{1,2},{0,2},{2,3},{3,4} // daftar edge
    };
    vector<double> prob = {0.5, 0.5, 0.2, 0.8, 0.9}; // probabilitas tiap edge
    int start = 0, end = 4; // titik awal dan akhir

    Solution s;
    s.maxProbability(n, edges, prob, start, end); // panggil fungsi utama
}
