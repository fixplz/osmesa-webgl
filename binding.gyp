{
	'targets': [
		{
			'target_name': 'webgl',
			'sources': [
				'src/bindings.cc',
				'src/webgl.cc',
			],
			'include_dirs': [
				'<!(node -e "require(\\"nan\\")")',
				'<!@(pkg-config osmesa --cflags-only-I | sed s/-I//g)'
			],
			'libraries': [
				'<!@(pkg-config osmesa --libs)'
			],
		}
	]
}
