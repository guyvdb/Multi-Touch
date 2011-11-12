
ROOT = File.dirname(__FILE__)

task :clean do

  patterns = [
    "**/Makefile",
    "bin/libmt.*",
    "bin/pc",
    "bin/dm",
    "bin/table",
    "bin/tiled",
    "bin/tmxviewer",
    "bin/*.so*",
    "build/*",
    "contrib/qjson/build/*",
    "contrib/tiled/bin/*",
    "**/*.o",    
    "**/moc_*",    
    "**/ui_*",
    "**/*~"
  ]

  patterns.each do |p|
    pattern = File.join(ROOT,p)
    Dir.glob(pattern).each do |file|
      system("rm -rf #{file}")
    end

  end

end
