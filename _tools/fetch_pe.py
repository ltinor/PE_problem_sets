#!/usr/bin/env python3
"""Fetch Project Euler problem descriptions."""
import urllib.request
import re
import sys

def fetch_problem(n):
    url = f"https://projecteuler.net/minimal={n}"
    try:
        req = urllib.request.Request(url, headers={
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36'
        })
        with urllib.request.urlopen(req, timeout=15) as resp:
            html = resp.read().decode('utf-8')
    except Exception as e:
        print(f"Error fetching problem {n}: {e}")
        return
    
    # Extract problem content
    m = re.search(r'<div[^>]*class="problem_content"[^>]*>(.*?)</div>\s*<div', html, re.DOTALL)
    if not m:
        m = re.search(r'<p>(.*?)</p>', html, re.DOTALL)
    
    if m:
        text = m.group(1)
        text = re.sub(r'<[^>]+>', '', text)
        text = re.sub(r'&lt;', '<', text)
        text = re.sub(r'&gt;', '>', text)
        text = re.sub(r'&amp;', '&', text)
        text = re.sub(r'&quot;', '"', text)
        text = re.sub(r'\s+', ' ', text).strip()
        print(f"\n=== PE {n} ===")
        print(text[:3000])
    else:
        print(f"Could not extract content for problem {n}")
        print("First 500 chars:", html[:500])

if __name__ == '__main__':
    for n in [711, 712, 713, 714, 715]:
        fetch_problem(n)
