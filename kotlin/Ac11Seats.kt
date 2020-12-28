package advenofcode

import java.nio.charset.StandardCharsets
import java.nio.file.Files
import java.nio.file.Paths

fun readInput(): Array<CharArray> {
    val path = Paths.get("").toAbsolutePath().parent
    val inputPath = Paths.get(path.toString(), "input", "11-seats.txt")
    var lines: List<String> = Files.readAllLines(inputPath, StandardCharsets.UTF_8)
    val nrow = lines.size
    val ncol = lines.get(0).length
    val occupation: Array<CharArray> = Array(nrow) { CharArray(ncol) }
    for (irow in 0..nrow - 1) {
        val line = lines.get(irow)
        for (icol in 0..line.length - 1) {
            occupation[irow][icol] = line[icol]
        }
    }
    return occupation
}

fun adjustRank(rank: Array<IntArray>, row: Int, col: Int, delta: Int) {
    val nrow = rank.size
    val ncol = rank[0].size
    for (irow in -1..1) {
        for (icol in -1..1) {
            if (icol == 0 && irow == 0) {
                continue
            }
            if (irow + row < 0 || irow + row >= nrow) {
                continue
            }
            if (icol + col < 0 || icol + col >= ncol) {
                continue
            }
            rank[irow + row][icol + col] += delta
        }
    }
}

fun calcConf1(occupation: Array<CharArray>, rank: Array<IntArray>): Boolean {
    val nrow = occupation.size
    val ncol = occupation[0].size
    var changed = false
    for (irow in 0..nrow - 1) {
        for (icol in 0..ncol - 1) {
            if (occupation[irow][icol] == 'L' && rank[irow][icol] == 0) {
                occupation[irow][icol] = '#'
                changed = true
            }
            if (occupation[irow][icol] == '#' && rank[irow][icol] >= 4) {
                occupation[irow][icol] = 'L'
                changed = true
            }
        }
    }
    return changed
}

fun calcConf2(occupation: Array<CharArray>, rank: Array<IntArray>): Boolean {
    val nrow = occupation.size
    val ncol = occupation[0].size
    var changed = false
    for (irow in 0..nrow - 1) {
        for (icol in 0..ncol - 1) {
            if (occupation[irow][icol] == 'L' && rank[irow][icol] == 0) {
                occupation[irow][icol] = '#'
                changed = true
            }
            if (occupation[irow][icol] == '#' && rank[irow][icol] >= 5) {
                occupation[irow][icol] = 'L'
                changed = true
            }
        }
    }
    return changed
}


fun calcRank(occupation: Array<CharArray>): Array<IntArray> {
    val nrow = occupation.size
    val ncol = occupation[0].size
    val rankNew = Array(occupation.size) { IntArray(occupation[0].size) { 0 } }
    for (irow in 0..nrow - 1) {
        for (icol in 0..ncol - 1) {
            if (occupation[irow][icol] == '#') {
                adjustRank(rankNew, irow, icol, 1)
            }
        }
    }
    return rankNew
}

fun calcRank2(occupation: Array<CharArray>): Array<IntArray> {
    val nrow = occupation.size
    val ncol = occupation[0].size
    val rankNew = Array(occupation.size) { IntArray(occupation[0].size) { 0 } }
    for (irow in 0..nrow - 1) {
        for (icol in 0..ncol - 1) {
            for (rdelta in -1..1) {
                for (coldelta in -1..1) {
                    var runner = 0
                    if (rdelta == 0 && coldelta == 0) {
                        continue
                    }
                    while (true) {
                        runner++
                        val x = irow + runner * rdelta
                        val y = icol + runner * coldelta
                        if (x < 0 || x >= nrow) {
                            break
                        }
                        if (y < 0 || y >= ncol) {
                            break
                        }
                        if (occupation[x][y] == '#') {
                            rankNew[irow][icol]++
                            break
                        }
                        if (occupation[x][y] == 'L') {
                            break
                        }
                    }
                }
            }
        }
    }
    return rankNew
}

fun countSeats(occupation: Array<CharArray>): Int {
    val nrow = occupation.size
    val ncol = occupation[0].size
    var counter = 0
    for (irow in 0..nrow - 1) {
        for (icol in 0..ncol - 1) {
            if (occupation[irow][icol] == '#') {
                counter++
            }
        }
    }
    return counter
}

fun main(args: Array<String>) {
    val occupation = readInput()
    val occupation2 = Array(occupation.size) { occupation[it].copyOf() }
    var rank: Array<IntArray> = Array(occupation.size) { IntArray(occupation[0].size) { 0 } }
    while (calcConf1(occupation, rank)) {
        rank = calcRank(occupation)
    }
    println("Occupied seat with rules part 1: " + countSeats(occupation))
    // part 2
    rank = calcRank2(occupation2)
    while (calcConf2(occupation2, rank)) {
        rank = calcRank2(occupation2)
    }
    println("Occupied seat with rules part 2: " + countSeats(occupation2))
}


