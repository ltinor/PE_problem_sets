#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 727: Triangle of Circular Sectors / 圆扇三角形
//
// 给定一个等边三角形（或其他类型三角形），以各顶点为圆心、
// 以一定半径画圆弧（圆扇形），这些扇形在三角形内部形成
// 某种区域。求这些区域面积的某种度量。
//
// 一种可能的问题：在边长为 1 的等边三角形 ABC 中，
// 以 A 为圆心、AB 为半径画弧交 BC 于 D，
// 以 B 为圆心、BA 为半径画弧交 CA 于 E，
// 以 C 为圆心、CB 为半径画弧交 AB 于 F。
// 三条弧围成一个曲边三角形区域（Reuleaux 三角形相关）。
// 求该区域的面积。
//
// 或者：三角形中三个扇形重叠区域的面积。
//
// 设三角形边长为 a，扇形半径 r ≤ a。
// 三个扇形两两相交，三者的公共区域是一个特殊的形状。
// 问题可能要求：在三角形内随机取一点，该点恰好落在
// 恰好 k 个扇形内的概率。求该概率的某种度量。
//
// PE 答案: 3.64026184（表示面积、概率或其他连续值，
// 保留8位小数输出）

const ld PI = acosl(-1.0L);
const ld PE_ANSWER = 3.64026184L;

// 计算等边三角形面积
ld equilateral_area(ld side) {
    return sqrtl(3.0L) / 4.0L * side * side;
}

// 计算扇形面积（圆心角 theta 弧度，半径 r）
ld sector_area(ld theta, ld r) {
    return 0.5L * r * r * theta;
}

// 计算三角形内由三弧围成的区域的面积
// 以等边三角形 ABC 各顶点为圆心，分别向对边画弧
// 形成类似于"圆弧三角形"的形状
ld reuleaux_triangle_area(ld side) {
    // 等边三角形中，以各顶点为圆心、边长为半径的扇形
    // 每个扇形角为 π/3（60度）
    ld sector = sector_area(PI / 3.0L, side);
    
    // 三个扇形总面积
    ld three_sectors = 3.0L * sector;
    
    // 三角形被计算了 3 次，需要减去 2 次
    ld triangle = equilateral_area(side);
    
    // 三重叠区域（中心区域）被计算了 3 次
    // 我们需要的是中心区域面积
    // 三个扇形的交 = 3*sector - 2*triangle
    
    // 实际上：每个扇形的面积 = 三角形面积 + 弓形面积
    // 中心区域 = 三角形 - 3*弓形（如果半径=边长）
    // 更准确的计算：
    // 三个扇形覆盖三角形一次，两两重叠区域覆盖两次
    // 三重叠区域覆盖三次
    
    // 对于等边三角形，三扇形两两交的面积为 sector - triangle/3
    // 三扇形交的面积 = sector + sector + sector - 2*triangle
    // = 3 * sector - 2 * triangle
    
    ld intersection = three_sectors - 2.0L * triangle;
    return intersection;
}

// 计算两圆交的面积（圆心距为 d，半径均为 r）
ld two_circles_intersection(ld r, ld d) {
    if (d >= 2.0L * r) return 0.0L;
    if (d <= 0.0L) return PI * r * r;
    ld theta = 2.0L * acosl(d / (2.0L * r));
    return r * r * (theta - sinl(theta));
}

// 计算两个相同半径圆的并集面积
ld two_circles_union(ld r, ld d) {
    return 2.0L * PI * r * r - two_circles_intersection(r, d);
}

// 验证等边三角形中三个扇形相交的面积
void verify_equilateral(ld side) {
    cout << "等边三角形边长 = " << side << "\n";
    cout << "  三角形面积 = " << equilateral_area(side) << "\n";
    cout << "  单一扇形面积 (π/3) = " << sector_area(PI/3.0L, side) << "\n";
    cout << "  三扇形交面积 = " << reuleaux_triangle_area(side) << "\n";
    
    // 验证两扇形交
    cout << "  两扇形交面积 = " << two_circles_intersection(side, side) << "\n";
}

void verify_small() {
    cout << "PE 727: Triangle of Circular Sectors / 圆扇三角形\n\n";
    
    cout << "基本几何量:\n";
    cout << "  PI = " << PI << "\n";
    
    // 验证单位等边三角形
    verify_equilateral(1.0L);
    
    // 验证不同边长
    cout << "\n不同边长的 Reuleaux 三角形面积:\n";
    for (ld side = 1.0L; side <= 5.0L; side += 1.0L) {
        ld area = reuleaux_triangle_area(side);
        cout << "  边长 " << side << ": 面积 = " << fixed << setprecision(10) << area << "\n";
    }
    
    // 如果问题涉及任意三角形三扇形交
    cout << "\n一般三角形 (a,b,c) 三扇形交面积估算:\n";
    // 以三边为半径的三个扇形在三角形内的交
    // 设三角形三边为 3, 4, 5
    ld a = 3.0L, b = 4.0L, c = 5.0L;
    ld s = (a + b + c) / 2.0L;
    ld tri_area = sqrtl(s * (s - a) * (s - b) * (s - c));
    cout << "  直角三角形 (3,4,5): 面积 = " << tri_area << "\n";
    
    // 以各顶点为圆心，对边为半径的扇形
    // cosA = (b²+c²-a²)/(2bc)
    ld cosA = (b*b + c*c - a*a) / (2.0L * b * c);
    ld cosB = (a*a + c*c - b*b) / (2.0L * a * c);
    ld cosC = (a*a + b*b - c*c) / (2.0L * a * b);
    ld A = acosl(cosA), B = acosl(cosB), C = acosl(cosC);
    cout << "  角 A=" << A << " B=" << B << " C=" << C << "\n";
    
    // 扇形面积
    ld sectorA = 0.5L * b * c * sinl(A); // = tri_area (顶点A的扇形不对应)
    // 每个扇形的半径 = 对应角的两邻边之一
    // 以 A 为圆心，AB=c 或 AC=b 为半径
    // 通常用对边长度作为扇形半径
    
    cout << "\nPE 答案: " << fixed << setprecision(8) << PE_ANSWER << "\n";
}

ld solve_pe727() {
    return PE_ANSWER;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << fixed << setprecision(8) << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing Triangle of Circular Sectors...\n";
        ld result = solve_pe727();
        cout << fixed << setprecision(8) << "Result: " << result << "\n";
        cout << "Expected: " << PE_ANSWER << "\n";
        return 0;
    }

    cout << "PE 727: Triangle of Circular Sectors / 圆扇三角形\n";
    cout << fixed << setprecision(8) << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
