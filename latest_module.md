## 使用方法

1. 将如下内容复制到你的项目的 submodule_helper.json
2. 修改root_folder的内容
3. 修改used 进行外设筛选
4. 根据你使用的平台修改 paCoreSrc 的仓库

### 注意点：

1. 不要修改rename

```json
{
    "root_folder": "./this should be changed according to your project structure/",
    "get_latest_templete_here": "https://github.com/ActivePeter/paMcuLib/blob/master/latest_module.md",
    "submodules_structure": {
        "paLibSubs": [
            {
                "used": 1,
                "git": "https://hub.fastgit.org/paMcuLib/paMcuLibCoreHead.git",
                "rename": "paCoreInc"
            },
            {
                "used": 1,
                "git": "https://hub.fastgit.org/paMcuLib/paMcuLibCore_stm32.git",
                "rename": "paCoreSrc"
            }
        ],
        "paLibSubs/paMods/display": [
            {
                "used": 1,
                "rename": "u8g2",
                "git": "https://hub.fastgit.org/paMcuLib/u8g2_paMcuLib.git"
            },
            {
                "used": 1,
                "rename": "ILI9341",
                "git": "https://hub.fastgit.org/paMcuLib/ili9341_paMcuLib.git"
            }
        ],
        "paLibSubs/paMods/input": [
            {
                "used": 1,
                "rename": "xpt2046",
                "git": "https://hub.fastgit.org/paMcuLib/xpt2046_paMcuLib.git"
            }
        ]
    }
}
```

