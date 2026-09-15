#!/usr/bin/env python3
"""Fetch and save Project Euler problem descriptions."""
import urllib.request
import re

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
        return None
    
    # Extract problem content
    m = re.search(r'<p>(.*?)</div>\s*<div[^>]*id="footer"', html, re.DOTALL)
    if not m:
        m = re.search(r'<p>(.*?)</div>', html, re.DOTALL)
    
    if m:
        text = m.group(1)
        text = re.sub(r'<[^>]+>', '', text)
        text = re.sub(r'&lt;', '<', text)
        text = re.sub(r'&gt;', '>', text)
        text = re.sub(r'&amp;', '&', text)
        text = re.sub(r'&quot;', '"', text)
        text = re.sub(r'\s+', ' ', text).strip()
        return text
    return None

for n in [711, 712, 713, 714, 715]:
    desc = fetch_problem(n)
    if desc:
        with open(f'PE{n}_desc.txt', 'w') as f:
            f.write(desc)
        print(f"=== PE {n} ({len(desc)} chars) ===")
        print(desc[:2000])
        print("...")
    else:
        print(f"Failed to fetch PE {n}")
    print()
