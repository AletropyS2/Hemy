newoption {
	 trigger = "lib",
	 description = "Set the lib type to static or shared",
	 allowed = {
		 { "shared", "Set library to shared (dll)" },
		 { "static", "Set library to static (lib)" }
	 },
	 default = "static"
}