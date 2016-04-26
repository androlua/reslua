#reslua

**本工具，是为了我的[JXM 2D游戏框架](https://github.com/niu2x/jxm)而写的。**

许多工具导出的资源描述是xml、json等，游戏是lua写的。

lua的一个优势就是既可以写逻辑，也可以写配置。

如果资源描述也是lua的话，我就不用花时间找库去在运行时解析json、xml。

##本工具的目标
像一个编译器一样工作，把xml、json提前转换成lua格式。

##JSON

test.json
  
    {
  	  "元件 2":{
  		  "type":"group",
  		  "children":{
  			  "图层 2":{
  				  "id":"元件 1",
  				  "x":14.05,
  				  "y":159.15,
  				  "angle":17.7474365234375,
  				  "sx":1.0000152587890625,
  				  "sy":1.0000152587890625
  			  },
  			  "图层 1":{
    				"id":"元件 1",
    				"x":-56,
    				"y":-69,
    				"angle":0,
    				"sx":1,
    				"sy":1
    			}
    		}
    	},
    	"元件 1":{
    		"type":"sprite",
    		"frameName":"元件 10000"
    	},
    	"元件 3":{
    		"type":"sprite",
    		"frameName":"元件 30000"
    	}
    }
    
**运行：** cat test.json|./json > test.lua

结果生成 test.lua

    local retJSON = {
    	["元件 2"] = {
    		["type"] = "group",
    		["children"] = {
    			["图层 2"] = {
    				["id"] = "元件 1",
    				["x"] = 14.050000,
    				["y"] = 159.149994,
    				["angle"] = 17.747437,
    				["sx"] = 1.000015,
    				["sy"] = 1.000015
    			},
    			["图层 1"] = {
    				["id"] = "元件 1",
    				["x"] = -56.000000,
    				["y"] = -69.000000,
    				["angle"] = 0.000000,
    				["sx"] = 1.000000,
    				["sy"] = 1.000000
    			}
    		}
    	},
    	["元件 1"] = {
    		["type"] = "sprite",
    		["frameName"] = "元件 10000"
    	},
    	["元件 3"] = {
    		["type"] = "sprite",
    		["frameName"] = "元件 30000"
    	}
    }
    return retJSON
    
**现在可以使用 local res = require 'test' 加载资源**

##XML

test.xml

    <plist version="1.0">
        <dict>
            <key>frames</key>
            <dict>
                <key>black-dog-000.jpg</key>
            </dict>
        </dict>
    </plist>
    
**运行：** cat test.xml|./xml > test.lua

test.lua

    local retXML = {
    	["name"] = "plist",
    	["type"] = "NT_GROUP",
    	["children"] = {
    		[1] = {
    			["name"] = "dict",
    			["type"] = "NT_GROUP",
    			["children"] = {
    				[1] = {
    					["name"] = "key",
    					["type"] = "NT_TEXT",
    					["text"] = "frames",
    					["attrs"] = {
    					}
    				},
    				[2] = {
    					["name"] = "dict",
    					["type"] = "NT_GROUP",
    					["children"] = {
    						[1] = {
    							["name"] = "key",
    							["type"] = "NT_TEXT",
    							["text"] = "black-dog-000.jpg",
    							["attrs"] = {
    							}
    						}
    					},
    					["attrs"] = {
    					}
    				}
    			},
    			["attrs"] = {
    			}
    		}
    	},
    	["attrs"] = {
    		["version"] = "1.0"
    	}
    }
    return retXML
    
##优势 和 缺陷
生成的lua文件比原始文件（xml或json）更大。

可以使用luac编译生成的lua，相当于对资源加密和压缩，但依然比原始文件大（哎呀我操）。

以往任何对lua代码使用的手段，现在都可以对资源文件使用了。

lua引擎加载资源，比我手写的xml解析快多了。。。但和libxml或别的库相比，快不快不知道。。。我没试过。。

