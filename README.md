# 主要功能：
* 中文菜单
* 许多来自 OneOfEleven 的模块：
   * AM 修复，显著提高接收质量
   * 长按按钮执行 F+ 操作的功能复制
   * 快速扫描
   * 菜单中的频道名称编辑
   * 频道名称 + 频率显示选项
   * 扫描列表分配的快捷方式（长按 `5 NOAA`）
   * 扫描时的扫描列表切换（在扫描时长按 `* Scan`）
   * 从菜单中可选择的可配置按钮功能
   * 状态栏上的电池百分比/电压，可从菜单中选择
   * 更长的背光时间
   * 麦克风条
   * 信号强度指示器（RSSI s-meter）
   * 更多的频率步进
   * 静噪更为敏感

* fagci 频谱分析仪（**F+5** 打开）
* 由我引入的一些其他修改：
   * SSB 解调（从 fagci 采用）
   * 背光调暗
   * 来自菜单的电池电压校准
   * 更好的电池百分比计算，可选择适用于 1600mAh 或 2200mAh
   * 更多可配置的按钮功能
   * 长按 MENU 作为另一个可配置按钮
   * 菜单中的更好的 DCS/CTCSS 扫描（在 RX DCS/CTCSS 菜单项中按 `* SCAN`）
   * Piotr022 信号强度样式
   * 使用 EXIT 停止扫描时还原初始频率/频道，使用 MENU 按钮记住上次找到的传输
   * 重新排序并重命名菜单条目
   * 修复 LCD 干扰崩溃问题




# 与最新版egzumer功能完全相同的中文固件

这个仓库是 OneOfEleven 定制固件与 fagci 频谱分析仪合并，并加入了egzumer的一些修改。
并在egzumer修改的基础上汉化菜单

[https://github.com/egzumer/uv-k5-firmware-custom](https://github.com/egzumer/uv-k5-firmware-custom)  
[https://github.com/OneOfEleven/uv-k5-firmware-custom](https://github.com/OneOfEleven/uv-k5-firmware-custom)  
[https://github.com/fagci/uv-k5-firmware-fagci-mod/tree/refactor](https://github.com/fagci/uv-k5-firmware-fagci-mod/tree/refactor)

所有这些都是 DualTachyon 的开源固件的克隆和定制版本，可以在以下位置找到：

[https://github.com/DualTachyon/uv-k5-firmware](https://github.com/DualTachyon/uv-k5-firmware) .. 一个很酷的成果！

在使用此固件时，请自担风险（全部）。绝对不能保证它在任何情况下都能在你的收音机上正常工作，它甚至可能会使你的收音机砖化，如果出现这种情况，你可能需要购买另一台收音机。

总之，玩得开心。

# 收音机性能

请注意，全胜 UV-Kx 收音机不是专业品质的收发器，它们的性能受到严格限制。RX 前端根本没有跟踪调谐的带通滤波，因此对大范围的频率信号都是宽带/全开放的。

在高强度射频环境中使用收音机很可能会使接收变得非常困难（AM 模式的影响远远大于 FM），接收机的动态范围并不大，这导致强信号的 AM 音频出现失真。在固件/软件中没有更多的操作可以改善这一点，一旦我所做的 RX 增益调整（AM 修复）达到硬件极限，你的 AM RX 音频几乎就不存在了（就像全胜的固件一样）。
另一方面，FM RX 音频应该是正常的。

但是，它们是价格不错的玩具，很有趣。

# 示例

<p float="left">
  <img src="/images/cn1.png" width=300 />
  <img src="/images/cn2.png" width=300 />
</p>


# 用户功能自定义

你可以通过启用/禁用各种编译选项来定制固件，这允许我们删除某些固件功能，以便在闪存中为其他功能腾出空间。你会在 "Makefile" 的顶部找到这些选项（'0' = 禁用，'1' = 启用）... 

（请注意：以下内容是一个示例，实际的 "Makefile" 可能会有所不同） 

```
ENABLE_CLANG                  := 0     **experimental, builds with clang instead of gcc (LTO will be disabled if you enable this)
ENABLE_SWD                    := 0       only needed if using CPU's SWD port (debugging/programming)
ENABLE_OVERLAY                := 0       cpu FLASH stuff, not needed
ENABLE_LTO                    := 0     **experimental, reduces size of compiled firmware but might break EEPROM reads (OVERLAY will be disabled if you enable this)
ENABLE_UART                   := 1       without this you can't configure radio via PC !
ENABLE_AIRCOPY                := 0       easier to just enter frequency with butts
ENABLE_FMRADIO                := 0       WBFM VHF broadcast band receiver
ENABLE_NOAA                   := 0       everything NOAA (only of any use in the USA)
ENABLE_VOICE                  := 0       want to hear voices ?
ENABLE_VOX                    := 0
ENABLE_ALARM                  := 0       TX alarms
ENABLE_1750HZ                 := 0       side key 1750Hz TX tone (older style repeater access)
ENABLE_PWRON_PASSWORD         := 1       power-on password stuff
ENABLE_BIG_FREQ               := 0       big font frequencies (like original QS firmware)
ENABLE_SMALL_BOLD             := 1       bold channel name/no. (when name + freq channel display mode)
ENABLE_KEEP_MEM_NAME          := 1       maintain channel name when (re)saving memory channel
ENABLE_WIDE_RX                := 1       full 18MHz to 1300MHz RX (though front-end/PA not designed for full range)
ENABLE_TX_WHEN_AM             := 0       allow TX (always FM) when RX is set to AM
ENABLE_F_CAL_MENU             := 0       enable the radios hidden frequency calibration menu
ENABLE_CTCSS_TAIL_PHASE_SHIFT := 1       standard CTCSS tail phase shift rather than QS's own 55Hz tone method
ENABLE_BOOT_BEEPS             := 0       gives user audio feedback on volume knob position at boot-up
ENABLE_SHOW_CHARGE_LEVEL      := 0       show the charge level when the radio is on charge
ENABLE_REVERSE_BAT_SYMBOL     := 1       mirror the battery symbol on the status bar (+ pole on the right)
ENABLE_NO_CODE_SCAN_TIMEOUT   := 1       disable 32-sec CTCSS/DCS scan timeout (press exit butt instead of time-out to end scan)
ENABLE_AM_FIX                 := 1       dynamically adjust the front end gains when in AM mode to helo prevent AM demodulator saturation, ignore the on-screen RSSI level (for now)
ENABLE_AM_FIX_SHOW_DATA       := 1       show debug data for the AM fix (still tweaking it)
ENABLE_SQUELCH_MORE_SENSITIVE := 0       make squelch levels a little bit more sensitive - I plan to let user adjust the values themselves
ENABLE_FASTER_CHANNEL_SCAN    := 0       increases the channel scan speed, but the squelch is also made more twitchy
ENABLE_RSSI_BAR               := 1       enable a dBm/Sn RSSI bar graph level inplace of the little antenna symbols
ENABLE_AUDIO_BAR              := 0       experimental, display an audio bar level when TX'ing
ENABLE_COPY_CHAN_TO_VFO       := 1       copy current channel into the other VFO. Long press `1 BAND` when in channel mode
ENABLE_SPECTRUM               := 1       fagci spectrum analizer, activated with `F` + `5 NOAA`
ENABLE_REDUCE_LOW_MID_TX_POWER:= 0       makes medium and low power settings even lower
ENABLE_BYP_RAW_DEMODULATORS   := 0       additional BYP (bypass?) and RAW demodulation options, prooved not to be very usefull, but it is there if you want to experiment
ENABLE_BLMIN_TMP_OFF          := 0       additional function for configurable buttons that toggles `BLMin` on and off wihout saving it to the EEPROM
```



# License

Copyright 2023 Dual Tachyon
https://github.com/DualTachyon

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.


