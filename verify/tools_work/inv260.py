#!/usr/bin/env python3
"""盘点 260 道 PE_DIFF 题：编译+PE探针实跑 vs 官方答案，静态提取 PE 分支片段分类。"""
import os, re, sys, json, subprocess
from concurrent.futures import ThreadPoolExecutor

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
GPP = r"F:\tools\mingw64\bin\g++.exe"
WORK = os.path.join(os.path.dirname(__file__), "inv260")
os.makedirs(WORK, exist_ok=True)

PIDS = """439 458 460 468 493 494 496 498 499 502 512 515 517 520 524 525 526 527
529 530 532 533 536 538 539 540 542 543 548 549 551 556 557 559 561 562
565 566 569 570 571 572 574 576 578 579 582 583 585 588 591 592 597 598
599 600 604 619 620 623 624 626 627 636 637 639 642 644 645 647 648 652
653 656 659 660 661 663 665 666 667 669 670 673 675 676 680 681 687 696
697 702 704 712 716 718 720 722 723 724 726 727 728 729 731 734 735 737
738 739 740 744 746 751 752 754 766 768 769 770 771 773 774 776 777 780
781 782 783 784 785 786 787 789 790 791 792 793 794 796 797 798 799 801
802 803 804 805 806 807 808 809 810 811 812 813 814 815 817 818 819 821
822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839
840 841 842 843 844 845 846 847 848 849 850 851 852 854 855 856 857 858
859 860 861 862 863 864 865 866 867 868 870 871 872 873 874 875 876 877
878 879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895
896 897 898 899 900 903 904 905 907 908 909 910 911 912 914 915 916 917
920 922 923 924 925""".split()

pe = json.load(open(os.path.join(ROOT, "_tools", "audit", "pe_answers.json")))

def one(pid):
    r = {"pid": pid}
    src_p = os.path.join(ROOT, pid, "code", "std.cpp")
    try:
        src = open(src_p, encoding="utf-8", errors="replace").read()
    except OSError as e:
        r["err"] = f"NO_SRC:{e}"; return r
    exe = os.path.join(WORK, f"{pid}.exe")
    c = subprocess.run([GPP, "-std=c++17", "-O2", src_p, "-o", exe],
                       capture_output=True, timeout=180)
    if c.returncode != 0:
        r["err"] = "COMPILE_FAIL:" + c.stderr.decode("utf-8", "replace")[-200:]
        return r
    try:
        p = subprocess.run([exe], input=b"PE\n", capture_output=True, timeout=30)
        out = p.stdout.decode("utf-8", "replace").replace("\r\n", "\n")
        lines = [l.strip() for l in out.split("\n") if l.strip()]
        r["rc"] = p.returncode
        r["got"] = lines[-1] if lines else ""
    except subprocess.TimeoutExpired:
        r["err"] = "PROBE_TLE"; return r
    off = pe.get(pid)
    r["official"] = off
    r["match"] = (r.get("got") == off)
    # 静态: PE 分支片段
    m = re.search(r'(?:if|else\s+if)\s*\(\s*(?:mode|first|s|cmd|query|op|arg|t)\s*==\s*"PE"\s*\)\s*\{', src)
    if not m:
        m = re.search(r'if\s*\([^()]*"PE"[^()]*\)\s*\{', src)
    if m:
        seg = src[m.start():m.start()+700]
        r["branch"] = seg[:650]
    # 静态: PE_ANS 类常量定义
    for cm in re.finditer(r'(?:const\s+\w+\s+|constexpr\s+\w+\s+)?(PE_\w+)\s*=\s*("?)([0-9][0-9.eE]*)\2', src):
        r.setdefault("consts", []).append([cm.group(1), cm.group(3)])
    return r

def main():
    res = []
    with ThreadPoolExecutor(max_workers=8) as ex:
        for r in ex.map(one, PIDS):
            res.append(r)
    match = [r for r in res if r.get("match")]
    mism = [r for r in res if not r.get("match") and not r.get("err")]
    errs = [r for r in res if r.get("err")]
    print(f"total={len(res)} match={len(match)} mismatch={len(mism)} err={len(errs)}")
    json.dump(res, open(os.path.join(WORK, "inventory.json"), "w",
                        encoding="utf-8"), ensure_ascii=False, indent=1)
    for r in errs:
        print(f"[{r['pid']}] ERR {r['err'][:120]}")
    print("--- mismatches ---")
    for r in mism:
        print(f"[{r['pid']}] got={r.get('got','')[:60]!r} official={r.get('official')!r}")

if __name__ == "__main__":
    main()
