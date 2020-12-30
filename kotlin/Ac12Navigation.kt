package advenofcode

import java.lang.Math.toRadians
import java.nio.charset.StandardCharsets
import java.nio.file.Files
import java.nio.file.Paths
import kotlin.math.*

class Ac12Navigation(
        var commands: List<String> = mutableListOf()
) {

    fun readInput() {
        val path = Paths.get("").toAbsolutePath().parent
        val inputPath = Paths.get(path.toString(), "input", "12-navigation.txt")
        commands = Files.readAllLines(inputPath, StandardCharsets.UTF_8)
    }

    fun apply1() {
        var x: Int = 0// W E
        var y: Int = 0// S N
        var angle = 0
        for (index in 0..commands.size - 1) {
            val command = commands[index]
            val d = command[0]
            val no = command.substring(1).toInt()
            if (d == 'E') {
                x += no
            }
            if (d == 'W') {
                x -= no
            }
            if (d == 'N') {
                y += no
            }
            if (d == 'S') {
                y -= no
            }
            if (d == 'R') {
                angle -= no
            }
            if (d == 'L') {
                angle += no

            }
            if (d == 'F') {
                x += no * cos(toRadians(angle.toDouble())).toInt()
                y += no * sin(toRadians(angle.toDouble())).toInt()
            }
        }
        println("Navigation by shifting")
        println(x)
        println(y)
        println(abs(x) + abs(y))
    }

    fun applyWaypoint() {
        var x: Int = 0// W E
        var y: Int = 0// S N
        var xw: Int = 10
        var yw: Int = 1
        for (index in 0..commands.size - 1) {
            val command = commands[index]
            var d = command[0]
            var no = command.substring(1).toInt()
            if (d == 'E') {
                xw += no
            }
            if (d == 'W') {
                xw -= no
            }
            if (d == 'N') {
                yw += no
            }
            if (d == 'S') {
                yw -= no
            }
            if (d == 'R' || d == 'L') {
                if (no == 270) {
                    d = if (d == 'R') 'L' else 'R'
                    no = 90
                }
                if (no == 180) {
                    xw = -xw
                    yw = -yw
                }
                if (no == 90) {
                    val xt = xw
                    if (d == 'R') {
                        xw = yw
                        yw = -xt
                    }
                    if (d == 'L') {
                        xw = -yw
                        yw = xt
                    }
                }
            }
            if (d == 'F') {
                x += no * xw
                y += no * yw
            }
        }
        println("Navigation by waypoint")
        println(x)
        println(y)
        println(abs(x) + abs(y))
    }
}


fun main(args: Array<String>) {
    var nav = Ac12Navigation()
    nav.readInput()
    nav.apply1()
    nav.applyWaypoint()
}
