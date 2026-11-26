#!/usr/bin/env bash
set -euo pipefail

BIN="./exercise3"
OUT_DIR="results"
mkdir -p "$OUT_DIR"

MIN_SIZE=1000
MAX_SIZE=10000
SIZE_INCR=1000
N_PERMS=100
N_KEYS=10000

# Ajusta MAX_JOBS al número de núcleos físicos (ej. 4 u 8) para no falsear clock()
MAX_JOBS=4

GENERATORS=("uniform" "potential" "gaussian")
ORDERS=("sorted" "unsorted")

run_case() {
    local gen="$1"
    local ord="$2"
    local met="$3"
    local outfile="${OUT_DIR}/${gen}_${ord}_${met}.dat"

    echo "[INICIO] gen=${gen} | order=${ord} | method=${met}"
    "$BIN" \
        --min-size "$MIN_SIZE" \
        --max-size "$MAX_SIZE" \
        --size_incr "$SIZE_INCR" \
        --n_perms "$N_PERMS" \
        --n_keys "$N_KEYS" \
        --generator "$gen" \
        --order "$ord" \
        --method "$met" \
        --output "$outfile"
    echo "[FIN]    -> $outfile"
}

job_count=0
for gen in "${GENERATORS[@]}"; do
    for ord in "${ORDERS[@]}"; do
        if [[ "$ord" == "sorted" ]]; then
            methods=("linear" "binary" "auto")
        else
            methods=("linear" "auto")
        fi

        for met in "${methods[@]}"; do
            run_case "$gen" "$ord" "$met" &
            ((job_count++))
            if (( job_count >= MAX_JOBS )); then
                wait -n
                ((job_count--))
            fi
        done
    done
done

wait
echo "Todas las 15 ejecuciones han terminado en ${OUT_DIR}/"
