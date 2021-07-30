
object Ac14Initialization extends App {

  def readLines(): Unit = {
    val wd = os.pwd
    val pth = wd/os.up/os.up
    val source = os.read(pth/"input"/"14-initialization.txt").lines()
    source.forEach(println(_))
  }

  readLines()
}