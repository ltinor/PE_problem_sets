#!/bin/bash
# Test PE 851-968: compile + run with "PE" input
# macOS compatible version
BASE="/Users/yini/Desktop/test/cpp/ProjectEuler"
TMPDIR=$(mktemp -d)
trap "rm -rf $TMPDIR" EXIT

echo "=========================================="
echo "PE 851-968 Verification Report"
echo "=========================================="
echo ""

COMPILE_FAIL=""
RUNTIME_FAIL=""
ANSWER_MISMATCH=""
ANSWER_OK=""
PLACEHOLDER=""
NOT_FOUND=""
COMPILE_OK_COUNT=0

# Helper: known answer lookup
known_answer() {
    case $1 in
        871) echo "497300941";;
        872) echo "622370484708689";;
        873) echo "644288016";;
        874) echo "75640242";;
        875) echo "130702327";;
        881) echo "183182007700";;
        882) echo "245143924";;
        883) echo "196246694";;
        884) echo "966580193";;
        885) echo "827759707";;
        886) echo "178245463";;
        887) echo "60.9112535";;
        888) echo "350608994";;
        889) echo "0.00801483";;
        890) echo "120592557";;
        891) echo "7541783";;
        892) echo "34683298";;
        893) echo "0.99993832";;
        894) echo "85516249";;
        895) echo "66687705";;
        896) echo "0.04860463";;
        897) echo "460088576432531620";;
        898) echo "0.69233750";;
        899) echo "0.13790397";;
        900) echo "840282274715517044";;
        *) echo "";;
    esac
}

DIRS=$(find "$BASE" -maxdepth 1 -type d \( -name "PE8[5-9]*" -o -name "PE9*" \) | sort)

for dir in $DIRS; do
    NUM=$(basename "$dir" | sed 's/PE//')
    if [ "$NUM" -lt 851 ] || [ "$NUM" -gt 968 ]; then
        continue
    fi
    
    CPP="$dir/code/std.cpp"
    if [ ! -f "$CPP" ]; then
        NOT_FOUND="$NOT_FOUND PE$NUM,"
        continue
    fi
    
    BIN="$TMPDIR/pe${NUM}"
    
    # Compile
    COMPILE_ERR=$(g++ -std=c++17 -O2 -o "$BIN" "$CPP" 2>&1)
    if [ $? -ne 0 ]; then
        COMPILE_FAIL="$COMPILE_FAIL PE$NUM,"
        continue
    fi
    
    COMPILE_OK_COUNT=$((COMPILE_OK_COUNT + 1))
    
    # Run with 60s timeout via perl
    OUTPUT=$(perl -e '
        $SIG{ALRM} = sub { die "timeout\n" };
        alarm(60);
        open(my $fh, "-|", $ARGV[0]) or die "exec: $!";
        local $/;
        my $out = <$fh>;
        close($fh);
        print $out;
    ' "$BIN" 2>/dev/null <<< "PE")
    EXIT_CODE=$?
    
    if [ $EXIT_CODE -ne 0 ]; then
        RUNTIME_FAIL="$RUNTIME_FAIL PE$NUM,"
        continue
    fi
    
    # Extract the answer - try to find a numeric answer
    ANSWER=$(echo "$OUTPUT" | grep -oE '^[0-9]+(\.[0-9]+)?$' | head -1)
    if [ -z "$ANSWER" ]; then
        ANSWER=$(echo "$OUTPUT" | grep -oE '[0-9]+(\.[0-9]+)?' | head -1)
    fi
    
    KNOWN=$(known_answer $NUM)
    
    if [ -n "$KNOWN" ]; then
        # 851-900 range
        if [ "$ANSWER" = "$KNOWN" ]; then
            ANSWER_OK="$ANSWER_OK PE$NUM,"
        else
            ANSWER_MISMATCH="$ANSWER_MISMATCH PE$NUM(got=$ANSWER,exp=$KNOWN),"
        fi
    else
        # 901-968 range
        if [ -z "$ANSWER" ] || [ "$ANSWER" = "0" ] || [ "$ANSWER" = "0.0" ] || [ "$ANSWER" = "0.0000000000" ]; then
            PLACEHOLDER="$PLACEHOLDER PE$NUM(ans=$ANSWER),"
        else
            ANSWER_OK="$ANSWER_OK PE$NUM(ans=$ANSWER),"
        fi
    fi
done

echo "=== COMPILE FAILURES ==="
echo "$COMPILE_FAIL" | tr ',' '\n' | grep -v '^$' | sed 's/^/  /'
[ -z "$COMPILE_FAIL" ] && echo "  (none)"
echo ""

echo "=== RUNTIME FAILURES (timeout/crash) ==="
echo "$RUNTIME_FAIL" | tr ',' '\n' | grep -v '^$' | sed 's/^/  /'
[ -z "$RUNTIME_FAIL" ] && echo "  (none)"
echo ""

echo "=== ANSWER MISMATCH (851-900) ==="
echo "$ANSWER_MISMATCH" | tr ',' '\n' | grep -v '^$' | sed 's/^/  /'
[ -z "$ANSWER_MISMATCH" ] && echo "  (none)"
echo ""

echo "=== PLACEHOLDER ANSWERS (901-968) ==="
echo "$PLACEHOLDER" | tr ',' '\n' | grep -v '^$' | sed 's/^/  /'
[ -z "$PLACEHOLDER" ] && echo "  (none)"
echo ""

echo "=== VERIFIED OK (correct answer) ==="
echo "$ANSWER_OK" | tr ',' '\n' | grep -v '^$' | sed 's/^/  /'
[ -z "$ANSWER_OK" ] && echo "  (none)"
echo ""

echo "=== SUMMARY ==="
echo "Compile OK: $COMPILE_OK_COUNT"
echo "Compile Fail: $(echo "$COMPILE_FAIL" | tr ',' '\n' | grep -c 'PE')"
echo "Runtime Fail: $(echo "$RUNTIME_FAIL" | tr ',' '\n' | grep -c 'PE')"
echo "Answer Verified: $(echo "$ANSWER_OK" | tr ',' '\n' | grep -c 'PE')"
echo "Answer Mismatch: $(echo "$ANSWER_MISMATCH" | tr ',' '\n' | grep -c 'PE')"
echo "Placeholder: $(echo "$PLACEHOLDER" | tr ',' '\n' | grep -c 'PE')"
