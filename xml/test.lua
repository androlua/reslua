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
