//BuildRoCC 是专门用于配置 RoCC key
//OpcodeSet.all：RoCC 接收所用自定义指令类型。
class WithLCMRoCCAccel extends Config((site,here,up) => {
    case BuildRoCC => Seq(       
        (p:Parameters) => {
            val regWidth = 64 // 寄存器位宽
            val lcmAccel = LazyModule(new LCMRoCCAccel(OpcodeSet.all, regWidth)(p))
            lcmAccel
        }
    )
})

//OpcodeSet object 定义以及自定义指令编码
object OpcodeSet {
  def custom0 = new OpcodeSet(Seq(Bits("b0001011")))
  def custom1 = new OpcodeSet(Seq(Bits("b0101011")))
  def custom2 = new OpcodeSet(Seq(Bits("b1011011")))
  def custom3 = new OpcodeSet(Seq(Bits("b1111011")))
  def all = custom0 | custom1 | custom2 | custom3
}

