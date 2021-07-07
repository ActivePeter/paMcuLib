## 使用方法

1. 将如下内容复制到你的项目的 submodule_helper.json
2. 修改root_folder的内容
3. 修改used 进行外设筛选
4. 根据你使用的平台修改 paCoreSrc 的仓库

### 注意点：

1. 不要修改rename

```json
{
    "root_folder": "./components/",
    "get_latest_templete_here": "https://github.com/ActivePeter/paMcuLib/blob/master/latest_module.md",
    "submodules_structure": {
        "paLibSubs": [
            {
                "used": 1,
                "git": "https://hub.fastgit.org/paMcuLib/paMcuLibCoreHead.git",
                "rename": "paCoreHead"
            },
            {
                "used": 1,
                "git": "https://hub.fastgit.org/paMcuLib/paMcuLibCore_Esp32.git",
                "rename": "paCoreSrc"
            },
            {
                "used": 1,
                "git": "https://hub.fastgit.org/ActivePeter/paMcuLib_Base.git",
                "rename": "paBase"
            }
        ],
        "paLibSubs/paMods/display": [
            {
                "used": 1,
                "rename": "SSD1306",
                "git": "https://hub.fastgit.org/paMcuLib/ssd1306_paMcuLib.git"
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

