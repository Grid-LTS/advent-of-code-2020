package advenofcode

import java.math.BigInteger
import java.nio.charset.StandardCharsets
import java.nio.file.Files
import java.nio.file.Paths

class Ac13BusDeparture
(var earliest: Int = 0,
 var buslinesString: List<String> = mutableListOf()) {
    fun readInput() {
        val path = Paths.get("").toAbsolutePath().parent
        val inputPath = Paths.get(path.toString(), "input", "13-bus-departure.txt")
        var lines = Files.readAllLines(inputPath, StandardCharsets.UTF_8)
        earliest = lines.get(0).toInt()
        var schedules = lines.get(1)
        buslinesString = schedules.split(",").map { it.trim() }
    }

    fun determineEarliestLine() {
        val buslinesFiltered = buslinesString.filter { !it.equals("x") }.map { it.toInt() }
        var waiting: Int = -1
        var lineNo = 0
        for (index in 0..buslinesFiltered.size - 1) {
            val period = buslinesFiltered.get(index)
            val rem = earliest % period
            val delta = period - rem
            if (waiting == -1) {
                waiting = delta
                lineNo = buslinesFiltered.get(index)
                continue
            }
            if (delta < waiting) {
                waiting = delta
                lineNo = buslinesFiltered.get(index)
            }
        }
        println("Line number:" + lineNo.toString())
        println(waiting.toString() + "min")
        println(waiting * lineNo)
    }

    fun determineEarliestCascadeTime() {
        // this algorithm assumes that busline Ids are prime numbers
        val buslinesInt = buslinesString.map { if (it.equals("x")) 0 else it.toInt() }
        val buslinesFiltered = buslinesInt.filter { it != 0 }
        var shifts = IntArray(buslinesFiltered.size) { 0 }
        var step = buslinesFiltered[0].toBigInteger()
        var earliest = buslinesFiltered[0].toBigInteger()
        for (i in 1 until buslinesFiltered.size) {
            var busId = buslinesFiltered[i].toBigInteger()
            var shift = buslinesInt.indexOf(buslinesFiltered[i]).toBigInteger()
            shifts[i] = shift.toInt() // needed for debugging
            var found = false
            while (!found) {
                if (earliest.add(shift).mod(busId) == BigInteger.ZERO) {
                    break
                }
                earliest += step
            }
            step = step.multiply(busId)
        }
        println(earliest)
    }
}

fun main(args: Array<String>) {
    var departures = Ac13BusDeparture()
    departures.readInput()
    departures.determineEarliestLine()
    departures.determineEarliestCascadeTime()
}