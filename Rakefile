
ROOT = File.dirname(__FILE__)

task :clean do

  # files
  files = [
    "**/Makefile",
    "linux/libmt.*",
    "linux/pc",
    "linux/dm",
    "linux/table",
    "linux/tiled",
    "linux/tmxviewer",
    "linux/tuio",
    "linux/*.so*",
    "build/*",
    "contrib/qjson/build/*",
    "contrib/tiled/bin/*",
    "**/*.o",    
    "**/moc_*",    
    "**/ui_*",
    "**/*~"
  ]

  files.each do |p|
    pattern = File.join(ROOT,p)
    Dir.glob(pattern).each do |file|
      system("rm -rf #{file}")
    end
  end

  #directories
  dirs = [
    "/contrib/tiled/build"
  ]

end
